#include "uploadSample.h"
#include <iomanip>

void uploadSample::showMainpage(const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) const
{
    callback( drogon::HttpResponse::newHttpViewResponse("sampleView.csp"));
}

void uploadSample::recieveUpload(const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) const
{
    drogon::MultiPartParser fileParser;
    
    auto resp = drogon::HttpResponse::newHttpResponse();

    if (fileParser.parse(req) != 0 || fileParser.getFiles().size() != 1)
    {
        resp->setBody("何かファイルを選んでください！");
        resp->setStatusCode(k403Forbidden);
        callback(resp);
        return;
    }
    
    auto &file = fileParser.getFiles()[0];
    if( isEnabledExtension(file.getFileExtension()) )
    {
        auto uploadDir = 
            createDirectoryName(
                drogon::app().getUploadPath()
            );
        file.save(uploadDir);
        resp->setBody("ファイルを受信して保存しました。");
        resp->setStatusCode(k200OK);
    }
    else 
    {
        resp->setBody("ふざけんじゃねぇぞ、ウィルスでも送る気だったか？");
        resp->setStatusCode(k415UnsupportedMediaType);
    }

    callback(resp);
}

bool uploadSample::isEnabledExtension(const std::string_view target) const noexcept
{
    auto result = false;
    for(auto enabled : enabledExtension)
    {
        result |= (target == enabled);
    }
    return result;
}

std::string uploadSample::createDirectoryName(const std::string &uploadRoot) const noexcept
{
    auto now = std::time( nullptr );
    auto localNow = *std::localtime( &now );
    std::ostringstream oss;
    oss << std::put_time( &localNow, "%Y_%m_%d" );
    return uploadRoot + "/" + oss.str(); 
}
