/*  Copyright (c) MediaArea.net SARL. All Rights Reserved.
 *
 *  Use of this source code is governed by a GPLv3+/MPLv2+ license that can
 *  be found in the License.html file in the root of the source tree.
 */

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// RESTAPI functions
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef RESTAPIH
#define RESTAPIH
//---------------------------------------------------------------------------

#include <string>
#include <vector>
#include "Container.h"

//---------------------------------------------------------------------------

namespace MediaConch {

//---------------------------------------------------------------------------

//***************************************************************************
// Class RESTAPI
//***************************************************************************

class RESTAPI
{
public:

    static const std::string API_VERSION;

    enum Reason
    {
        NO_REASON,
        FILE_NOT_EXISTING,
        ID_NOT_EXISTING,
        NOT_READY,
    };

    enum Report
    {
        NO_REPORT,
        POLICY,
        IMPLEMENTATION,
        MEDIAINFO,
        MEDIATRACE,
    };

    std::string get_Report_string(Report r)
    {
#define ReportString(report) \
        case report:         \
            return #report;

        switch (r)
        {
            ReportString(POLICY);
            ReportString(IMPLEMENTATION);
            ReportString(MEDIAINFO);
            ReportString(MEDIATRACE);
            default:
                break;
        }
#undef ReportString
        return std::string();
    }

    Report string_to_Report(std::string str)
    {
#define ReportString(report)       \
        if (!str.compare(#report)) \
            return report;

        ReportString(POLICY);
        ReportString(IMPLEMENTATION);
        ReportString(MEDIAINFO);
        ReportString(MEDIATRACE);

#undef ReportString

        return NO_REPORT;
    }

    std::string get_Reason_string(Reason r)
    {
#define ReasonString(reason) \
        case reason:         \
            return #reason;

        switch (r)
        {
            ReasonString(FILE_NOT_EXISTING);
            ReasonString(ID_NOT_EXISTING);
            ReasonString(NOT_READY);
            default:
                break;
        }
#undef ReasonString
        return std::string();
    }

    Reason string_to_Reason(std::string str)
    {
#define ReasonString(reason)       \
        if (!str.compare(#reason)) \
            return reason;

        ReasonString(FILE_NOT_EXISTING);
        ReasonString(ID_NOT_EXISTING);
        ReasonString(NOT_READY);

#undef ReasonString

        return NO_REASON;
    }

    // Analyze
    struct Analyze_Arg
    {
        Analyze_Arg() : has_force_analyze(false) {}
        std::string            to_str() const;
        std::string            file;
        int                    id;
        bool                   has_force_analyze;
        bool                   force_analyze;
    };

    struct Analyze_Req
    {
        std::vector<Analyze_Arg> args;
        std::string              to_str() const;
    };

    struct Analyze_Ok
    {
        int                    inId;
        int                    outId;
        bool                   create;
        std::string            to_str() const;
    };

    struct Analyze_Nok
    {
        int                    id;
        Reason                 error;
        std::string            to_str() const;
    };

    struct Analyze_Res
    {
        ~Analyze_Res();
        std::vector<Analyze_Ok*>  ok;
        std::vector<Analyze_Nok*> nok;
        std::string               to_str() const;
    };

    // Status
    struct Status_Req
    {
        std::vector<int>        ids;
        std::string             to_str() const;
    };

    struct Status_Ok
    {
        Status_Ok() : has_percent(false) {}
        int                     id;
        bool                    finished;
        bool                    has_percent;
        double                  done;
        std::string             to_str() const;
    };

    struct Status_Nok
    {
        int                     id;
        Reason                  error;
        std::string             to_str() const;
    };

    struct Status_Res
    {
        ~Status_Res();
        std::vector<Status_Ok*>  ok;
        std::vector<Status_Nok*> nok;
        std::string              to_str() const;
    };

    // Report
    struct Report_Req
    {
        std::vector<int>         ids;
        std::vector<Report>      reports;
        std::vector<std::string> policies_names;
        std::vector<std::string> policies_contents;
        std::string              display_name;
        std::string              display_content;
        std::string              to_str() const;
    };

    struct Report_Ok
    {
        Report_Ok() :           has_valid(false) {}
        std::string             report;
        bool                    has_valid;
        bool                    valid;
        std::string             to_str() const;
    };

    struct Report_Nok
    {
        int                     id;
        Reason                  error;
        std::string             to_str() const;
    };

    struct Report_Res
    {
        ~Report_Res();
        Report_Ok                ok;
        std::vector<Report_Nok*> nok;
        std::string              to_str() const;
    };

    // Retry
    struct Retry_Req
    {
        std::vector<int>        ids;
        std::string             to_str() const;
    };

    struct Retry_Nok
    {
        int                     id;
        Reason                  error;
        std::string             to_str() const;
    };

    struct Retry_Res
    {
        ~Retry_Res();
        std::vector<int>        ok;
        std::vector<Retry_Nok*> nok;
        std::string             to_str() const;
    };

    // Clear
    struct Clear_Req
    {
        std::vector<int>        ids;
        std::string             to_str() const;
    };

    struct Clear_Nok
    {
        int                     id;
        Reason                  error;
        std::string             to_str() const;
    };

    struct Clear_Res
    {
        ~Clear_Res();
        std::vector<int>        ok;
        std::vector<Clear_Nok*> nok;
        std::string             to_str() const;
    };

    // List
    struct List_Req
    {
    };

    struct List_File
    {
        std::string            file;
        int                    id;
    };

    struct List_Res
    {
        ~List_Res();
        std::vector<List_File*> files;
        std::string             to_str() const;
    };

    // Validate
    struct Validate_Req
    {
        std::vector<int>           ids;
        Report                     report;
        std::vector<std::string>   policies_names;
        std::vector<std::string>   policies_contents;
        std::string                to_str() const;
    };

    struct Validate_Ok
    {
        Validate_Ok() :            valid(false) {}
        int                        id;
        bool                       valid;
        std::string                to_str() const;
    };

    struct Validate_Nok
    {
        int                        id;
        Reason                     error;
        std::string                to_str() const;
    };

    struct Validate_Res
    {
        ~Validate_Res();
        std::vector<Validate_Ok*>  ok;
        std::vector<Validate_Nok*> nok;
        std::string                to_str() const;
    };

    struct File_From_Id_Req
    {
        int          id;
        std::string  to_str() const;
    };

    struct File_From_Id_Res
    {
        std::string  file;
        std::string  to_str() const;
    };

public:
    //Constructor/Destructor
    RESTAPI();
    virtual ~RESTAPI();

    // Serialize: Request
    std::string serialize_analyze_req(Analyze_Req& req);
    std::string serialize_status_req(Status_Req& req);
    std::string serialize_report_req(Report_Req& req);
    std::string serialize_retry_req(Retry_Req& req);
    std::string serialize_clear_req(Clear_Req& req);
    std::string serialize_list_req(List_Req& req);
    std::string serialize_validate_req(Validate_Req& req);
    std::string serialize_file_from_id_req(File_From_Id_Req& req);

    // Serialize: Result
    std::string serialize_analyze_res(Analyze_Res& res);
    std::string serialize_status_res(Status_Res& res);
    std::string serialize_report_res(Report_Res& res);
    std::string serialize_retry_res(Retry_Res& res);
    std::string serialize_clear_res(Clear_Res& res);
    std::string serialize_list_res(List_Res& res);
    std::string serialize_validate_res(Validate_Res& res);
    std::string serialize_file_from_id_res(File_From_Id_Res& res);

    // Parse: Request
    Analyze_Req      *parse_analyze_req(std::string data);
    Status_Req       *parse_status_req(std::string data);
    Report_Req       *parse_report_req(std::string data);
    Retry_Req        *parse_retry_req(std::string data);
    Clear_Req        *parse_clear_req(std::string data);
    List_Req         *parse_list_req(std::string data);
    Validate_Req     *parse_validate_req(std::string data);
    File_From_Id_Req *parse_file_from_id_req(std::string data);

    // Parse: URI Request
    Analyze_Req      *parse_uri_analyze_req(const std::string& uri);
    Status_Req       *parse_uri_status_req(const std::string& uri);
    Report_Req       *parse_uri_report_req(const std::string& uri);
    Retry_Req        *parse_uri_retry_req(const std::string& uri);
    Clear_Req        *parse_uri_clear_req(const std::string& uri);
    List_Req         *parse_uri_list_req(const std::string& uri);
    Validate_Req     *parse_uri_validate_req(const std::string& uri);
    File_From_Id_Req *parse_uri_file_from_id_req(const std::string& uri);

    // Parse: Request
    Analyze_Res      *parse_analyze_res(std::string data);
    Status_Res       *parse_status_res(std::string data);
    Report_Res       *parse_report_res(std::string data);
    Retry_Res        *parse_retry_res(std::string data);
    Clear_Res        *parse_clear_res(std::string data);
    List_Res         *parse_list_res(std::string data);
    Validate_Res     *parse_validate_res(std::string data);
    File_From_Id_Res *parse_file_from_id_res(std::string data);

    std::string get_error() const { return error; }

private:
    Container *model;

    std::string error;

    //Helper
    Container::Value serialize_analyze_args(std::vector<Analyze_Arg>& args);
    Container::Value serialize_ids(std::vector<int>& ids);
    Container::Value serialize_report_reports(std::vector<Report>& args);
    Container::Value serialize_report_string(const std::string& args);
    Container::Value serialize_report_arr_str(const std::vector<std::string>& reports);
    Container::Value serialize_generic_nok(int id, Reason error);
    Container::Value serialize_analyze_oks(std::vector<Analyze_Ok*>& array);
    Container::Value serialize_status_oks(std::vector<Status_Ok*>& array);
    Container::Value serialize_report_ok(Report_Ok& ok);
    Container::Value serialize_list_file(const std::string& file, int id);
    Container::Value serialize_validate_ok(Validate_Ok* ok);

    int parse_analyze_arg(Container::Value *v, std::vector<Analyze_Arg>& args);
    int parse_report_reports(Container::Value *v, std::vector<Report>& reports);
    int parse_generic_nok(Container::Value *v, int& id, Reason& error);
    int parse_analyze_ok(Container::Value *v, std::vector<Analyze_Ok*>& ok);
    int parse_status_ok(Container::Value *v, std::vector<Status_Ok*>& ok);
    int parse_report_ok(Container::Value *v, Report_Ok& ok);
    int parse_list_file(Container::Value *v, std::string& file, int& id);
    int parse_validate_ok(Container::Value *v, std::vector<Validate_Ok*>& oks);

    RESTAPI (const RESTAPI&);
    RESTAPI& operator=(const RESTAPI&);
};

}

#endif
