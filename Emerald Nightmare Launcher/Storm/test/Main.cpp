
/*////////////////////////////////////////////////////////////////////////
// StormProxy code 
// Handles command line arguments from Emerald Nightmare Launcher
// Based on StormLib Test
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Stormproxy, Copyright (C) 2012 Marforius CC BY-NC-ND
// Stormlib, and all related code Copyright (C) 2010 Ladislav Zezula
//////////////////////////////////////////////////////////////////////////
// http://creativecommons.org/licenses/by-nc-nd/3.0/
//////////////////////////////////////////////////////////////////////////
// A very big thanks to Ladik for this great library, I hardly had to put
// any work at all into this thanks to you.
////////////////////////////////////////////////////////////////////////*/


#define _CRT_SECURE_NO_DEPRECATE
#define __INCLUDE_CRYPTOGRAPHY__
#define __STORMLIB_SELF__                   // Don't use StormLib.lib

#include "../src/StormLib.h"
#include "../src/StormCommon.h"
#include "../src/MD5_File.h"
#include "boost/program_options.hpp"

using namespace std;
namespace bfs = boost::filesystem;
namespace bpo = boost::program_options;
using namespace boost::this_thread;

#pragma warning(disable: 4505)              // 'XXX' : unreferenced local function has been removed
#pragma warning(disable: 4706)              // assignment within conditional expression
#pragma warning(disable: 4996)
#pragma warning(disable: 4512)              // assignment operator could not be generated
#define countof( array ) ( sizeof( array )/sizeof( array[0] ) )

static void MergeLocalPath(TCHAR * szBuffer, const char * szPart1, const char * szPart2)
	{
	// Copy directory name
	while(*szPart1 != 0)
		*szBuffer++ = *szPart1++;

	// Add separator
	*szBuffer++ = _T('/');

	// Copy file name
	while(*szPart2 != 0)
		*szBuffer++ = *szPart2++;

	// Terminate the string
	*szBuffer = 0;
	}

static int inline CopyArchiveToArchive(const TCHAR * szMpqName, const TCHAR * szMpqCopyName, const char * szListFile)
	{
	char buffer[MAX_PATH];
	GetCurrentDirectory(sizeof(buffer),buffer);

	std:: string WorkDirForExtract = std:: string(buffer) + "\\Work";

	TCHAR  szLocalFile[MAX_PATH];
	HANDLE hMpq1 = NULL;                // Handle of existing archive
	HANDLE hMpq2 = NULL;                // Handle of archive to copy to
	int nError = ERROR_SUCCESS;

	// If no listfile or an empty one, use NULL
	if(szListFile == NULL || *szListFile == 0)
		szListFile = NULL;

	// Open the existing MPQ archive
	if(nError == ERROR_SUCCESS)
		{
		_tprintf(_T("Opening %s ...\n"), szMpqName);
		if(!SFileOpenArchive(szMpqName, 0, 0, &hMpq1))
			nError = GetLastError();
		}

	// Open the archive to copy to
	if(nError == ERROR_SUCCESS)
		{
		_tprintf(_T("Opening %s ...\n"), szMpqCopyName);
		if(!SFileOpenArchive(szMpqCopyName, 0, 0, &hMpq2))
			nError = GetLastError();
		}

	SFileSetMaxFileCount(hMpq2, 0x00080000);

	// Copy files in folders that already exist from one archive to another
	// this function needs to
	// delete files that are flagged for deletion inside the mpq inside all archives involved (patch-3 would delete a file in patch and patch-2 or the copy-to archive)
	// extract the copy-to archive, identify the names of folders
	// look for folders of the same name inside the copy-to archive that are also inside the patch archives
	// extract from the patch archives and place the patched files inside the copy-to archive
	if(nError == ERROR_SUCCESS)
		{
		SFILE_FIND_DATA sf;
		HANDLE hFind = SFileFindFirstFile(hMpq1, "*", &sf, szListFile);
		bool bResult = true;

		_tprintf(_T("Copying files ...\n"));

		if(hFind != NULL)
			{
			while(bResult)
				{
				if(strcmp(sf.cFileName, LISTFILE_NAME) && strcmp(sf.cFileName, ATTRIBUTES_NAME))
					{
					SFileSetLocale(sf.lcLocale);



					// Create the local file name
					MergeLocalPath(szLocalFile, WorkDirForExtract.c_str(), sf.szPlainName);
					if(SFileExtractFile(hMpq1, sf.cFileName, szLocalFile))
						{
						printf("Extracting %s ... OK\n", sf.cFileName);
						if(!SFileAddFile(hMpq2, szLocalFile, sf.cFileName, sf.dwFileFlags))
							{
							nError = GetLastError();
							printf("Adding %s ... Failed\n\n", sf.cFileName);
							_tremove(szLocalFile);
							break;
							}
						else
							{
							printf("Adding %s ... OK\n", sf.cFileName);
							}
						}
					else
						{
						printf("Extracting %s ... Failed\n", sf.cFileName);
						}

					// Delete the added file
					_tremove(szLocalFile);
					}

				// Find the next file
				bResult = SFileFindNextFile(hFind, &sf);
				}

			// Close the search handle
			SFileFindClose(hFind);
			printf("\n");
			}
		}

	// Close both archives
	if(hMpq2 != NULL)
		SFileCloseArchive(hMpq2);
	if(hMpq1 != NULL)
		SFileCloseArchive(hMpq1);

	remove(szMpqName);
	return nError;
	}

inline void VerifyMPQSignature(const char *szFileName)
	{
	HANDLE hMpq = NULL;
	cout << endl;
	cout << "Opening file \"" << szFileName << "\"" << "..." << endl;

	if(SFileOpenArchive(szFileName, 0, 0, &hMpq))
		{
		switch(SFileVerifyArchive(hMpq))
			{

		case ERROR_VERIFY_FAILED:
			cout << "Failed to verify signature." << endl;
			cout << "Press any key to continue checking." << endl;
			cin.get();
			break;

		case ERROR_WEAK_SIGNATURE_OK:
			cout << "Weak signature is OK." << endl;
			break;

		case ERROR_WEAK_SIGNATURE_ERROR:
			cout << "Weak signature mismatch." << endl;
			cout << "Press any key to continue checking." << endl;
			cin.get();
			break;

		case ERROR_STRONG_SIGNATURE_OK:
			cout << "Strong signature is OK." << endl;
			break;

		case ERROR_STRONG_SIGNATURE_ERROR:
			cout << "Strong signature mismatch." << endl;
			cout << "Press any key to continue checking." << endl;
			cin.get();
			break;

		default:
			cout << "File passed internal signature checks, if there were any." << endl;
			break;

			}

		// if repacked, set HT to max
		char buffer[MAX_PATH];
		GetCurrentDirectory(sizeof(buffer),buffer);
		std:: string PatchEnUS3MPQ = std:: string(buffer) + "\\Data\\enUS\\patch-enUS-3.MPQ";
		boost::filesystem::path IsRepacked(PatchEnUS3MPQ);
		if( !boost::filesystem::exists(IsRepacked) )
			{
			SFileSetMaxFileCount(hMpq, 0x00080000);
			}

		SFileCloseArchive(hMpq);

		MD5 md5 ;
		cout << "Calculating MD5 of file, this may take time." << endl;

		// returns string, compare it with original or repacked MD5 - set MHT before function (if repacked)

		char *EstablishedMD5s [] = {
			// Original 3.3.5A (no mods)
			"17d340dbd0ac02569d56cd0d96b2c8b7",
			"325452ce19054ee76f29acb14da85884",
			"c48af167bd3253f4762dd077112252af",
			"6c9f85caf621ee546dbfe8811315eb11",
			"ab3a08a2993caec2db8c2c181f5f5065",
			"35733b76fcf0f95a0d8240d1f36cc5c3",
			"88e4545c0074f9d6c1eced7e035bdf6e",
			"6e099a82d9d2bb75c037625aecaa34aa",
			"2aa2c2c6aa341977ec15ee75d13a2429",
			"0423b93701903133e282247b74822364",
			"c9b1786849ade7f399c57da8c61fe352",
			"4077b16db9fe39f81fadbb2098ece280",
			"af01bc97ca87104c589d4d84684d3b4e",
			"be2a6737bb323b700c3d750ca9b72709",
			"6a2d75fad8d317b0bedaa4f82f9340a5",
			"2352dfdbb85174d80b748a1111c56ee9",
			"5514621925fa8cd17e864fabcbf85b4a",
			"273cc8a0137dbc6f978c74acaa809098",
			"965021d466779f68407965f4759c5cc6"
			// end original 3.3.5A (no mods)
			};

		bool IsKnownArchive=false;
		string CalculatedArchiveMD5 = md5.digestFile(szFileName);

		cout << CalculatedArchiveMD5 << endl;

		for ( int n=0; n < countof(EstablishedMD5s); n++ )
			{
			if (CalculatedArchiveMD5 == EstablishedMD5s[n])
				{
				cout << "Archive integrity is good. MD5 matched."<< endl;
				IsKnownArchive=true; // this is set to true to prevent the error message from coming up which is below
				// stop iterating md5s
				n = countof(EstablishedMD5s);
				}
			}

		if (IsKnownArchive == false)
			{
			cout << "File does NOT match any known MD5, archive is corrupt or changed!" << endl;
			cin.get();
			}

		delete [] szFileName;
		cout << endl;
		}
	}

inline void VerifyMPQPipe()
	{

	char buffer[MAX_PATH];
	GetCurrentDirectory(sizeof(buffer),buffer);

	std:: string CommonMPQ2 = std:: string(buffer) + "\\Data\\Common-2.MPQ";
	std:: string CommonMPQ = std:: string(buffer) + "\\Data\\Common.MPQ";
	std:: string ExpansionMPQ = std:: string(buffer) + "\\Data\\expansion.MPQ";
	std:: string LichkingMPQ = std:: string(buffer) + "\\Data\\lichking.MPQ";
	std:: string PatchMPQ = std:: string(buffer) + "\\Data\\patch.MPQ";
	std:: string Patch2MPQ = std:: string(buffer) + "\\Data\\patch-2.MPQ";
	std:: string Patch3MPQ = std:: string(buffer) + "\\Data\\patch-3.MPQ";
	std:: string Patch4MPQ = std:: string(buffer) + "\\Data\\patch-4.MPQ";
	std:: string BackupEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\backup-enUS.MPQ";
	std:: string BaseEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\base-enUS.MPQ";
	std:: string ExpansionLocaleEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\expansion-locale-enUS.MPQ";
	std:: string ExpansionSpeechEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\expansion-speech-enUS.MPQ";
	std:: string LichkingLocaleEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\lichking-locale-enUS.MPQ";
	std:: string LichkingSpeechEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\lichking-speech-enUS.MPQ";
	std:: string LocaleEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\locale-enUS.MPQ";
	std:: string PatchEnUS2MPQ = std:: string(buffer) + "\\Data\\enUS\\patch-enUS-2.MPQ";
	std:: string PatchEnUS3MPQ = std:: string(buffer) + "\\Data\\enUS\\patch-enUS-3.MPQ";
	std:: string PatchEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\patch-enUS.MPQ";
	std:: string SpeechEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\speech-enUS.MPQ";


	boost::filesystem::path IsRepacked(PatchEnUS3MPQ);
	if( !boost::filesystem::exists(IsRepacked) )
		{
		cout << "Detected files as being repacked." << endl;
		VerifyMPQSignature(CommonMPQ.c_str());
		VerifyMPQSignature(CommonMPQ2.c_str());
		VerifyMPQSignature(ExpansionMPQ.c_str());
		VerifyMPQSignature(LichkingMPQ.c_str());
		VerifyMPQSignature(PatchMPQ.c_str());

		VerifyMPQSignature(ExpansionLocaleEnUSMPQ.c_str());
		VerifyMPQSignature(ExpansionSpeechEnUSMPQ.c_str());
		VerifyMPQSignature(LichkingLocaleEnUSMPQ.c_str());
		VerifyMPQSignature(LichkingSpeechEnUSMPQ.c_str());
		VerifyMPQSignature(LocaleEnUSMPQ.c_str());
		VerifyMPQSignature(PatchEnUSMPQ.c_str());
		VerifyMPQSignature(SpeechEnUSMPQ.c_str());
		}
	else if( boost::filesystem::exists(IsRepacked) )
		{
		cout << "Detected files as being original 3.3.5A layout." << endl;

		VerifyMPQSignature(CommonMPQ2.c_str());
		VerifyMPQSignature(CommonMPQ.c_str());
		VerifyMPQSignature(ExpansionMPQ.c_str());
		VerifyMPQSignature(LichkingMPQ.c_str());
		VerifyMPQSignature(Patch2MPQ.c_str());
		VerifyMPQSignature(Patch3MPQ.c_str());
		VerifyMPQSignature(Patch4MPQ.c_str());
		VerifyMPQSignature(PatchMPQ.c_str());

		VerifyMPQSignature(BackupEnUSMPQ.c_str());
		VerifyMPQSignature(BaseEnUSMPQ.c_str());
		VerifyMPQSignature(ExpansionLocaleEnUSMPQ.c_str());
		VerifyMPQSignature(ExpansionSpeechEnUSMPQ.c_str());
		VerifyMPQSignature(LichkingLocaleEnUSMPQ.c_str());
		VerifyMPQSignature(LichkingSpeechEnUSMPQ.c_str());
		VerifyMPQSignature(LocaleEnUSMPQ.c_str());
		VerifyMPQSignature(PatchEnUS2MPQ.c_str());
		VerifyMPQSignature(PatchEnUS3MPQ.c_str());
		VerifyMPQSignature(PatchEnUSMPQ.c_str());
		VerifyMPQSignature(SpeechEnUSMPQ.c_str());
		}
	cout << endl;
	cout << "Signature/MD5 check complete. Press any key to exit." << endl;
	cin.get();
	}

inline void DeleteArchiveInterfaceFiles()
	{
	char buffer[MAX_PATH];
	GetCurrentDirectory(sizeof(buffer),buffer);
	std:: string PatchEnUS3MPQ = std:: string(buffer) + "\\Data\\enUS\\patch-enUS-3.MPQ";
	boost::filesystem::path IsRepacked(PatchEnUS3MPQ);
	if( !boost::filesystem::exists(IsRepacked) )
		{
		// do work
		}
	else if( boost::filesystem::exists(IsRepacked) )
		{
		cout << "If you were to delete your interface files you would damage your version of warcraft, aborting." << endl;
		cout << "If you want to play with this function, download Marforius-Client and repack your client's master patch files." << endl;
		cin.get();
		}
	}

inline void RepackArchives()
	{
	exit(0); // B E C A U S E - if you knew that this was unfinished you wouldn't have ran this function
	// repacker finds files from all files in data and puts
	// the files from the patch mpq archives into the master files
	// I was just combining the patch files here and I decided to stop coding this for a bit
	// i'll come back to this later

	char buffer[MAX_PATH];
	GetCurrentDirectory(sizeof(buffer),buffer);

	std:: string CommonMPQ2 = std:: string(buffer) + "\\Data\\Common-2.MPQ";
	std:: string CommonMPQ = std:: string(buffer) + "\\Data\\Common.MPQ";
	std:: string ExpansionMPQ = std:: string(buffer) + "\\Data\\expansion.MPQ";
	std:: string LichkingMPQ = std:: string(buffer) + "\\Data\\lichking.MPQ";
	std:: string PatchMPQ = std:: string(buffer) + "\\Data\\patch.MPQ";
	std:: string Patch2MPQ = std:: string(buffer) + "\\Data\\patch-2.MPQ";
	std:: string Patch3MPQ = std:: string(buffer) + "\\Data\\patch-3.MPQ";
	std:: string Patch4MPQ = std:: string(buffer) + "\\Data\\patch-4.MPQ";
	std:: string BackupEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\backup-enUS.MPQ";
	std:: string BaseEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\base-enUS.MPQ";
	std:: string ExpansionLocaleEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\expansion-locale-enUS.MPQ";
	std:: string ExpansionSpeechEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\expansion-speech-enUS.MPQ";
	std:: string LichkingLocaleEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\lichking-locale-enUS.MPQ";
	std:: string LichkingSpeechEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\lichking-speech-enUS.MPQ";
	std:: string LocaleEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\locale-enUS.MPQ";
	std:: string PatchEnUS2MPQ = std:: string(buffer) + "\\Data\\enUS\\patch-enUS-2.MPQ";
	std:: string PatchEnUS3MPQ = std:: string(buffer) + "\\Data\\enUS\\patch-enUS-3.MPQ";
	std:: string PatchEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\patch-enUS.MPQ";
	std:: string SpeechEnUSMPQ = std:: string(buffer) + "\\Data\\enUS\\speech-enUS.MPQ";

	boost::filesystem::path IsRepacked(PatchEnUS3MPQ);
	if( !boost::filesystem::exists(IsRepacked) )
		{
		cout << "Detected files as being repacked." << endl;
		cout << "Nothing to do." << endl;
		cin.get();
		}
	else if( boost::filesystem::exists(IsRepacked) )
		{
		CopyArchiveToArchive(Patch2MPQ.c_str(), PatchMPQ.c_str(), NULL);
		CopyArchiveToArchive(Patch3MPQ.c_str(), PatchMPQ.c_str(), NULL);
		CopyArchiveToArchive(PatchEnUS2MPQ.c_str(), PatchEnUSMPQ.c_str(), NULL);
		CopyArchiveToArchive(PatchEnUS3MPQ.c_str(), PatchEnUSMPQ.c_str(), NULL);
		remove(BackupEnUSMPQ.c_str());
		remove(BaseEnUSMPQ.c_str());
		}
	cout << endl;
	cout << "Repack complete, running MD5 check on repacked archives." << endl;
	// investigate
	VerifyMPQSignature(PatchMPQ.c_str());
	VerifyMPQSignature(PatchEnUSMPQ.c_str());
	// Add code to verify if matches MD5 to continue repacking after combining archives 
	}


int main(int ac, char* av[])
	{

	bfs::path wowexe("wow.exe");

	if( !bfs::exists(wowexe) )
		{
		cout << "Wow.exe not detected, nothing will work - exiting" << endl;
		cin.get();
		return 1;
		}

	if (ac == 1)
		{
		cout << "This program must be called from the launcher." << endl;
		cin.get();
		return 0;
		}

	bpo::options_description options("command line options");
	options.add_options() ("help", "Use -h or --help to list all arguments")
		("RunCHECKARCHIVES", "Check MD5 and signature of MPQ archives")
		("Repack", "Repack patch MPQ files into parent files")
		("RunDELETEARCHIVEINTERFACEFILES", "Delete archived interface/xml/lua/toc folders - only usable on Marforius-Client");

	bpo::variables_map vmap;

	try{
		bpo::store(
			bpo::parse_command_line(ac, av, options), vmap);
		bpo::notify(vmap);

		if (vmap.count("RunCHECKARCHIVES")) {
			VerifyMPQPipe();
			}

		if (vmap.count("Repack")) {
			RepackArchives();
			}

		if (vmap.count("RunDELETEARCHIVEINTERFACEFILES")) {
			DeleteArchiveInterfaceFiles();
			}
		}catch ( std::exception e ) // Not a valid arg
		{
		cout << options << endl;
			}
		return 0;
	}
