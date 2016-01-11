/*  Copyright (c) MediaArea.net SARL. All Rights Reserved.
 *
 *  Use of this source code is governed by a GPLv3+/MPLv2+ license that can
 *  be found in the License.html file in the root of the source tree.
 */

//---------------------------------------------------------------------------
#include <vector>
#include <algorithm>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifdef MEDIAINFO_DLL_RUNTIME
    #include "MediaInfoDLL/MediaInfoDLL.h"
    #define MediaInfoNameSpace MediaInfoDLL
#elif defined MEDIAINFO_DLL_STATIC
    #include "MediaInfoDLL/MediaInfoDLL_Static.h"
    #define MediaInfoNameSpace MediaInfoDLL
#else
    #include "MediaInfo/MediaInfoList.h"
    #define MediaInfoNameSpace MediaInfoLib
#endif
#if defined(_MSC_VER) && defined(UNICODE)
    #include "io.h"
    #include "fcntl.h"
#endif
#include "CLI.h"
#include "CommandLine_Parser.h"
#include "MediaInfo/MediaInfo.h"
#include "MediaInfo/MediaInfo_Events.h"
//---------------------------------------------------------------------------

//****************************************************************************
// Event to manage
//****************************************************************************

void Log_0 (struct MediaInfo_Event_Log_0* Event, struct UserHandle_struct* UserHandler)
{
    (void)UserHandler;
    MediaInfoLib::String MessageString;

    if (Event->Type>=0xC0)
        MessageString+=__T("E: ");

    #if defined(UNICODE) || defined (_UNICODE)
        MessageString+=Event->MessageStringU;
    #else //defined(UNICODE) || defined (_UNICODE)
        MessageString+=Event->MessageStringA;
    #endif //defined(UNICODE) || defined (_UNICODE)

    //Special cases
    switch (Event->MessageCode)
    {
        case 0xF1010101 : MessageString+=__T(" If you want to use such protocols, compile libcurl with SSL/SSH support"); break;
        case 0xF1010102 :
        case 0xF1010103 : MessageString+=__T(" If you are in a secure environment, do \"ssh %YourServerName%\" in order to add the fingerprint to the known_hosts file. If you want to ignore security issues, use --Ssh_IgnoreSecurity option"); break;
        case 0xF1010104 : MessageString+=__T(" If you want to ignore security issues, use --Ssl_IgnoreSecurity option."); break;
        default         : ;
    }

    if (Event->Type>=0x80)
        STRINGERR(MessageString);
    else
        STRINGOUT(MessageString);
}

//****************************************************************************
// The callback function
//****************************************************************************

void __stdcall Event_CallBackFunction(unsigned char* Data_Content, size_t Data_Size, void* UserHandler_Void)
{
    //*integrity tests
    if (Data_Size<4)
        return; //There is a problem

    //*Retrieving UserHandler
    struct UserHandle_struct*           UserHandler=(struct UserHandle_struct*)UserHandler_Void;
    struct MediaInfo_Event_Generic*     Event_Generic=(struct MediaInfo_Event_Generic*) Data_Content;


    //*Retrieving EventID
    //MediaInfo_int8u     ParserID    =(MediaInfo_int8u) ((Event_Generic->EventCode&0xFF000000)>>24);
    MediaInfo_int16u    EventID     =(MediaInfo_int16u)((Event_Generic->EventCode&0x00FFFF00)>>8 );
    MediaInfo_int8u     EventVersion=(MediaInfo_int8u) ( Event_Generic->EventCode&0x000000FF     );

    //*Global to all parsers
    switch (EventID)
    {
        case MediaInfo_Event_Log                                                    : if (EventVersion==0 && Data_Size>=sizeof(struct MediaInfo_Event_Log_0)) Log_0((struct MediaInfo_Event_Log_0*)Data_Content, UserHandler); break;
        default                                                                     : ;
    }
}

//***************************************************************************
// Main
//***************************************************************************

//---------------------------------------------------------------------------
int main(int argc, char* argv_ansi[])
{
    //Localisation
    setlocale(LC_ALL, "");
    MediaInfoLib::MediaInfo::Option_Static(__T("CharSet"), __T(""));

    //Initialize terminal (to fix Unicode output on Win32)
    #if defined(_MSC_VER) && defined(UNICODE)
        _setmode(_fileno(stdout), _O_U8TEXT);
        _setmode(_fileno(stderr), _O_U8TEXT);
    #endif
    MediaInfoLib::MediaInfo::Option_Static(__T("LineSeparator"), __T("\n")); //Using sdtout

    // TODO: Retrieve command line (mainly for Unicode)
    GETCOMMANDLINE();
    std::vector<std::string> args;
    for (int i = 0; i < argc; ++i)
    {
        MediaInfoLib::String Argument(argv[i]);
        args.push_back(ZenLib::Ztring(Argument).To_UTF8());
    }

    MediaConch::CLI cli;

    int ret = cli.parse_args(args);
    if (ret == CLI_RETURN_ERROR)
        return 1;
    else if (ret == CLI_RETURN_FINISH)
        return 0;

    if (cli.init() < 0)
        return 1;

    //Callback for error handling
    CallBack_Set(&cli, (void*)Event_CallBackFunction);

    if ((ret = cli.run()) < 0)
        cli.print_error((MediaConch::MediaConchLib::errorHttp)ret);

    cli.finish();

    return 0;
}
