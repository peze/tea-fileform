// This file is auto-generated, don't edit it. Thanks.
#ifndef DARABONBA_FILE_FORM_HPP_H_
#define DARABONBA_FILE_FORM_HPP_H_
#include <darabonba/core.hpp>
using namespace std;
using json = nlohmann::json;
namespace Darabonba {

#define FILE_FORM_ERROR(name) \
  if(j.find(#name) != j.end() || j[#name].is_null()) {             \
    Error("##name is empty");              \
  }
  /**
   * The model is for genrating stream
   */
  class FileField : public Darabonba::Model {
  public:
    FileField() {}
    FileField(const json &map);
    friend void to_json(json& j, const FileField& p){
      DARABONBA_JSON_TO(filename, filename)
      DARABONBA_JSON_TO(contentType, contentType)
      DARABONBA_JSON_TO(content, content)

    }
    friend void from_json(const json& j, FileField& p){
      FILE_FORM_ERROR(filename)
      FILE_FORM_ERROR(contentType)
      FILE_FORM_ERROR(content)
      DARABONBA_JSON_FROM(filename, filename, string)
      DARABONBA_JSON_FROM(contentType, contentType, string)
      DARABONBA_JSON_FROM(content, content, string)
    }

    json toMap(){
      json map;
      to_json(map, *this);
      return map;
    };
    void validate(const json &map) {};

    string filename() const {
      if(_filename) {
        return *_filename;
      }
      return "";
    }
    void setFilename(string filename) {
      _filename = make_shared<string> (filename);
    }
    string contentType() const {
      if(_contentType) {
        return *_contentType;
      }
      return "";
    }
    void setContentType(string contentType) {
      _contentType = make_shared<string> (contentType);
    }
    string content() const {
      if(_content) {
        return *_content;
      }
      return "";
    }
    void setContent(string content) {
      _content = make_shared<string> (content);
    }
    ~FileField() = default;
  private:
    // the name of the file
    shared_ptr<string> _filename;

    // the MIME of the file
    shared_ptr<string> _contentType;

    // the content of the file
    shared_ptr<string> _content;

  };

  class FileFormStream: public RequestBody {
  public:
    FileFormStream()=default;
    ~FileFormStream() {
      curl_formfree(_formPost);
    };
    FileFormStream(const json& form):
        _form(form), RequestBody(){};
    void read(CURL* curl);
    struct curl_slist* headerChecker(struct curl_slist* list);
  private:
    json _form;
    struct curl_httppost* _formPost = NULL;
  };


  class FileForm {
  public:
    FileForm() {}

    ~FileForm() {
    }
    /**
     * Gets a boundary string
     * @return the random boundary string
     */
    static string getBoundary();

    /**
     * Give a form and boundary string, wrap it to a readable stream
     * @param form The form map
     * @param boundary the boundary string
     * @return the readable from file form
     */
    static shared_ptr<FileFormStream> toFileForm(const json &form, const string &boundary);

  };



}
#endif
