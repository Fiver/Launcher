/////////////////////////////////////////////////////////////////////////
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
#define _CRT_SECURE_NO_DEPRECATE
#define __INCLUDE_CRYPTOGRAPHY__
#define __STORMLIB_SELF__                   // Don't use StormLib.lib

#include "../src/StormLib.h"
#include "../src/StormCommon.h"
#include "../src/MD5_File.h"
#include <boost/program_options.hpp>

using namespace std;
namespace bfs = boost::filesystem;
namespace bpo = boost::program_options;
using namespace boost::this_thread;

#pragma warning(disable: 4505)              // 'XXX' : unreferenced local function has been removed
#pragma warning(disable: 4706)              // assignment within conditional expression
#pragma warning(disable: 4996)
#pragma warning(disable: 4512)              // assignment operator could not be generated
#define countof( array ) ( sizeof( array )/sizeof( array[0] ) )
int IsRunningRepackOps;

//************************************
// Method:    MergeLocalPath
// FullName:  MergeLocalPath
// Access:    public static
// Returns:   void
// Qualifier:
// Parameter: TCHAR * szBuffer
// Parameter: const char * szPart1
// Parameter: const char * szPart2
//************************************
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

//************************************
// Method:    CopyArchiveToArchive
// FullName:  CopyArchiveToArchive
// Access:    public static
// Returns:   int
// Qualifier:
// Parameter: const TCHAR * szMpqName
// Parameter: const TCHAR * szMpqCopyName
// Parameter: const char * szListFile
// Comment: Copies one archive to another
//************************************
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

//************************************
// Method:    ContinueRepack
// FullName:  ContinueRepack
// Access:    public
// Returns:   void
// Qualifier:
// Parameter: const char * szFileName
// Comment: Continues repacking patches after they are combined and checked
//************************************
inline void ContinueRepack(const char *szFileName)
	{
	cout << szFileName << endl; // just to shut the compiler up
	// unfinished
	}

//************************************
// Method:    VerifyArchiveMD5
// FullName:  VerifyArchiveMD5
// Access:    public
// Returns:   void
// Qualifier:
// Parameter: const char * szFileName
// Parameter: bool RepackingMD5Check
// Comment: Check internal MPQ signature and MD5 against a internal list of valid MD5s
//************************************
inline void VerifyArchiveMD5(const char *szFileName, bool RepackingMD5Check)
	{
	HANDLE hMpq = NULL;

	if(SFileOpenArchive(szFileName, 0, 0, &hMpq))
		{
		switch(SFileVerifyArchive(hMpq))
			{

		case ERROR_VERIFY_FAILED:
			cout << "Archive: \""<<szFileName<<"\" Failed to verify signature." << endl;
			break;

		case ERROR_WEAK_SIGNATURE_OK:
			cout << "Archive: \""<<szFileName<<"\" Weak signature is OK." << endl;
			break;

		case ERROR_WEAK_SIGNATURE_ERROR:
			cout << "Archive: \""<<szFileName<<"\" Weak signature mismatch." << endl;
			break;

		case ERROR_STRONG_SIGNATURE_OK:
			cout << "Archive: \""<<szFileName<<"\" Strong signature is OK." << endl;
			break;

		case ERROR_STRONG_SIGNATURE_ERROR:
			cout << "Archive: \""<<szFileName<<"\" Strong signature mismatch." << endl;
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

		for ( int n=0; n < countof(EstablishedMD5s); n++ )
			{
			if (CalculatedArchiveMD5 == EstablishedMD5s[n])
				{
				cout << "Archive \""<<szFileName<<"\" integrity is good. MD5 matched." << endl;
				IsKnownArchive=true; // this is set to true to prevent the error message from coming up which is below
				// stop iterating md5s
				n = countof(EstablishedMD5s);
				}
			}

		if (IsKnownArchive == false)
			{
			if (RepackingMD5Check)
				{
				string YesCheck;
				cout << "It would seem archive: \""<<szFileName<<"\"  has been damaged by the combination operation, or you are running a customized client already." << endl
					<< "Abort and restore original file? Y/N:" << endl;
				cin >> YesCheck;
				if (YesCheck != "Y")
					{
					// restore original file
					}
				}
			else if (!RepackingMD5Check)
				{
				cout << "File \""<<szFileName<<"\" does NOT match any known MD5, archive is corrupt or changed!" << endl;
				}
			// write to log, for lazy saving of MD5s later on when I add more to the list of valid MD5s
			ofstream myfile;
			myfile.open("Logs\\MD5-Check.log");
			myfile << "A MD5 was unmatched in this archive Archive: \""<<szFileName<<"\"" << endl
				<< CalculatedArchiveMD5 << endl << endl;
			myfile.close();
			}

		delete [] szFileName;
		cout << endl;

		if (RepackingMD5Check)
			{
			cout << "Continuing repack operation" << endl;
			IsRunningRepackOps++;

			if (IsRunningRepackOps == 2)
				{
				ContinueRepack(szFileName);
				}
			}
		}
	}

//************************************
// Method:    VerifyMPQPipe
// FullName:  VerifyMPQPipe
// Access:    public
// Returns:   void
// Qualifier:
// Comment: Builds directory strings and feeds them to VerifyArchiveMD5
//************************************
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
		boost::thread MD5Thread1(
			boost::bind(&VerifyArchiveMD5, CommonMPQ.c_str(), false));
		boost::thread MD5Thread2(
			boost::bind(&VerifyArchiveMD5, CommonMPQ2.c_str(), false));
		boost::thread MD5Thread3(
			boost::bind(&VerifyArchiveMD5, ExpansionMPQ.c_str(), false));
		boost::thread MD5Thread4(
			boost::bind(&VerifyArchiveMD5, LichkingMPQ.c_str(), false));
		boost::thread MD5Thread5(
			boost::bind(&VerifyArchiveMD5, PatchMPQ.c_str(), false));

		boost::thread MD5Thread6(
			boost::bind(&VerifyArchiveMD5, ExpansionLocaleEnUSMPQ.c_str(), false));
		boost::thread MD5Thread7(
			boost::bind(&VerifyArchiveMD5, ExpansionSpeechEnUSMPQ.c_str(), false));
		boost::thread MD5Thread8(
			boost::bind(&VerifyArchiveMD5, LichkingLocaleEnUSMPQ.c_str(), false));
		boost::thread MD5Thread9(
			boost::bind(&VerifyArchiveMD5, LichkingSpeechEnUSMPQ.c_str(), false));
		boost::thread MD5Thread10(
			boost::bind(&VerifyArchiveMD5, LocaleEnUSMPQ.c_str(), false));
		boost::thread MD5Thread11(
			boost::bind(&VerifyArchiveMD5, PatchEnUSMPQ.c_str(), false));
		boost::thread MD5Thread12(
			boost::bind(&VerifyArchiveMD5, SpeechEnUSMPQ.c_str(), false));

		// Messy
		MD5Thread1.join();
		MD5Thread2.join();
		MD5Thread3.join();
		MD5Thread4.join();
		MD5Thread5.join();
		MD5Thread6.join();
		MD5Thread7.join();
		MD5Thread8.join();
		MD5Thread9.join();
		MD5Thread10.join();
		MD5Thread11.join();
		MD5Thread12.join();
		}
	else if( boost::filesystem::exists(IsRepacked) )
		{
		cout << "Detected files as being original 3.3.5A layout." << endl;

		boost::thread MD5Thread1(
			boost::bind(&VerifyArchiveMD5, CommonMPQ2.c_str(), false));
		boost::thread MD5Thread2(
			boost::bind(&VerifyArchiveMD5, CommonMPQ.c_str(), false));
		boost::thread MD5Thread3(
			boost::bind(&VerifyArchiveMD5, ExpansionMPQ.c_str(), false));
		boost::thread MD5Thread4(
			boost::bind(&VerifyArchiveMD5, LichkingMPQ.c_str(), false));
		boost::thread MD5Thread5(
			boost::bind(&VerifyArchiveMD5, Patch2MPQ.c_str(), false));
		boost::thread MD5Thread6(
			boost::bind(&VerifyArchiveMD5, Patch3MPQ.c_str(), false));
		boost::thread MD5Thread7(
			boost::bind(&VerifyArchiveMD5, Patch4MPQ.c_str(), false));
		boost::thread MD5Thread8(
			boost::bind(&VerifyArchiveMD5, PatchMPQ.c_str(), false));

		boost::thread MD5Thread9(
			boost::bind(&VerifyArchiveMD5, BackupEnUSMPQ.c_str(), false));
		boost::thread MD5Thread10(
			boost::bind(&VerifyArchiveMD5, BaseEnUSMPQ.c_str(), false));
		boost::thread MD5Thread11(
			boost::bind(&VerifyArchiveMD5, ExpansionLocaleEnUSMPQ.c_str(), false));
		boost::thread MD5Thread12(
			boost::bind(&VerifyArchiveMD5, ExpansionSpeechEnUSMPQ.c_str(), false));
		boost::thread MD5Thread13(
			boost::bind(&VerifyArchiveMD5, LichkingLocaleEnUSMPQ.c_str(), false));
		boost::thread MD5Thread14(
			boost::bind(&VerifyArchiveMD5, LichkingSpeechEnUSMPQ.c_str(), false));
		boost::thread MD5Thread15(
			boost::bind(&VerifyArchiveMD5, LocaleEnUSMPQ.c_str(), false));
		boost::thread MD5Thread16(
			boost::bind(&VerifyArchiveMD5, PatchEnUS2MPQ.c_str(), false));
		boost::thread MD5Thread17(
			boost::bind(&VerifyArchiveMD5, PatchEnUS3MPQ.c_str(), false));
		boost::thread MD5Thread18(
			boost::bind(&VerifyArchiveMD5, PatchEnUSMPQ.c_str(), false));
		boost::thread MD5Thread19(
			boost::bind(&VerifyArchiveMD5, SpeechEnUSMPQ.c_str(), false));

		// Messy
		MD5Thread1.join();
		MD5Thread2.join();
		MD5Thread3.join();
		MD5Thread4.join();
		MD5Thread5.join();
		MD5Thread6.join();
		MD5Thread7.join();
		MD5Thread8.join();
		MD5Thread9.join();
		MD5Thread10.join();
		MD5Thread11.join();
		MD5Thread12.join();
		MD5Thread13.join();
		MD5Thread14.join();
		MD5Thread15.join();
		MD5Thread16.join();
		MD5Thread17.join();
		MD5Thread18.join();
		MD5Thread19.join();
		}
	}

inline void VerifyMPQThreadPipe()
	{
	boost::thread MD5ThreadMaster(
		boost::bind(&VerifyMPQPipe));
	MD5ThreadMaster.join();

	cout << "Signature/MD5 check complete. Press any key to exit." << endl;
	cin.get();
	}

//************************************
// Method:    DeleteArchiveInterfaceFiles
// FullName:  DeleteArchiveInterfaceFiles
// Access:    public
// Returns:   void
// Qualifier:
// Comment: Delete Interface folder within MPQ archive after the client has been repacked (for use only with Marforius-Client)
//************************************
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

//************************************
// Method:    RepackArchives
// FullName:  RepackArchives
// Access:    public
// Returns:   void
// Qualifier:
// Comment: Copies files from sub-patch archives to parent-patch archives then checks their MD5 before continuing operations on them
//************************************
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
	// investigate
	VerifyArchiveMD5(PatchMPQ.c_str(), true);
	VerifyArchiveMD5(PatchEnUSMPQ.c_str(), true);
	// Add code to verify if matches MD5 to continue repacking after combining archives
	}

//************************************
// Method:    main
// FullName:  main
// Access:    public
// Returns:   int
// Qualifier:
// Parameter: int ac
// Parameter: char * av[]
// Args: --RunCHECKARCHIVES, --Repack, --RunDELETEARCHIVEINTERFACEFILES
//************************************
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

	try {
		bpo::store(
			bpo::parse_command_line(ac, av, options), vmap);
		bpo::notify(vmap);

		if (vmap.count("RunCHECKARCHIVES")) {
			VerifyMPQThreadPipe();
			}

		if (vmap.count("Repack")) {
			RepackArchives();
			}

		if (vmap.count("RunDELETEARCHIVEINTERFACEFILES")) {
			DeleteArchiveInterfaceFiles();
			}
		} catch ( std::exception e ) // Not a valid arg
		{
		cout << options << endl;
			}
		return 0;
	}
