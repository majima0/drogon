#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class uploadSample : public drogon::HttpController<uploadSample>
{
    public:
    METHOD_LIST_BEGIN
    METHOD_ADD(uploadSample::showMainpage, "/", Get);
    METHOD_ADD(uploadSample::recieveUpload, "/upload", Post);
    METHOD_LIST_END

    private:
    std::vector<std::string> enabledExtension;
    bool isEnabledExtension(const std::string_view) const noexcept;
    std::string createDirectoryName(const std::string &) const noexcept;

    public:
    uploadSample():
    enabledExtension({"png", "jpg", "bmp", "svg"})
    {}

    void showMainpage(const HttpRequestPtr &,
            std::function<void(const HttpResponsePtr &)> &&callback) const;

    void recieveUpload(const HttpRequestPtr &,
            std::function<void(const HttpResponsePtr &)> &&callback) const;
};
