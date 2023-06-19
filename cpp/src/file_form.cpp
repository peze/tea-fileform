// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/file_form.hpp>
#include <iostream>
#include <map>

using namespace std;

char asciiToLower(char in) {
  if (in <= 'Z' && in >= 'A')
    return in - ('Z' - 'z');
  return in;
}

Darabonba::FileField::FileField(const json &map) : Darabonba::Model() {
  validate(map);
  from_json(map, *this);
}

string Darabonba::FileForm::getBoundary() {
  return Darabonba::Core::uuid();
}

shared_ptr<Darabonba::FileFormStream> Darabonba::FileForm::toFileForm(const json &form, const string &boundary) {
  return shared_ptr<Darabonba::FileFormStream>(new FileFormStream(form));
}

struct curl_slist* Darabonba::FileFormStream::headerChecker(struct curl_slist* list) {
  struct curl_slist* head = list;
  while(head != nullptr) {
    string data = head->data;
    transform(data.begin(), data.end(), data.begin(), asciiToLower);
    if(data.rfind("content-type", 0) == 0) {
      head->data = "content-type: multipart/form-data";
    }
    head = head->next;
  }
  return list;
}

void Darabonba::FileFormStream::read(CURL* curl) {
  struct curl_httppost *lastPtr = NULL;

  for (json::iterator it = _form.begin(); it != _form.end(); ++it) {
    try {
      Darabonba::FileField file = it.value().get<Darabonba::FileField>();
      curl_formadd(&_formPost,
                   &lastPtr,
                   CURLFORM_COPYNAME, it.key().c_str(),
                   CURLFORM_FILE, file.content().c_str(),
                   CURLFORM_CONTENTTYPE, file.contentType().c_str(),
                   CURLFORM_END);
    } catch (exception ex) {
      curl_formadd(&_formPost,
                   &lastPtr,
                   CURLFORM_COPYNAME, it.key().c_str(),
                   CURLFORM_COPYCONTENTS, it.value().dump().c_str(),
                   CURLFORM_END);
    }
  }


  curl_easy_setopt(curl, CURLOPT_HTTPPOST, _formPost);
}