#include <iostream>
#include <curl/curl.h>

int main() {
  // Initialize cURL.
  CURL* curl = curl_easy_init();

  // Create a new document.
  std::string url =
      "https://firestore.googleapis.com/v1/projects/YOUR_PROJECT_ID/databases/(default)/documents/users/new_user";
  std::string data =
      R"({"fields": {"name": {"stringValue": "John Doe"}, "age": {"integerValue": "30"}}})";
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)data.size());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
  CURLcode res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    std::cerr << "Failed to create document: " << curl_easy_strerror(res)
              << std::endl;
  }

  // Read a document.
  url =
      "https://firestore.googleapis.com/v1/projects/YOUR_PROJECT_ID/databases/(default)/documents/users/new_user";
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  std::string response;
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  res = curl_easy_perform(curl);
  if (res == CURLE_OK) {
    std::cout << "Document contents: " << response << std::endl;
  } else {
    std::cerr << "Failed to read document: " << curl_easy_strerror(res)
              << std::endl;
  }

  // Update a document.
  url =
      "https://firestore.googleapis.com/v1/projects/YOUR_PROJECT_ID/databases/(default)/documents/users/new_user";
  data = R"({"fields": {"age": {"integerValue": "35"}}})";
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)data.size());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
  res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    std::cerr << "Failed to update document: " << curl_easy_strerror(res)
              << std::endl;
  }

  // Delete a document.
  url =
      "https://firestore.googleapis.com/v1/projects/YOUR_PROJECT_ID/databases/(default)/documents/users/new_user";
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    std::cerr << "Failed to delete document: " << curl_easy_strerror(res)
              << std::endl;
  }

  // Clean up.
  curl_easy_cleanup(curl);
  return 0;
}
