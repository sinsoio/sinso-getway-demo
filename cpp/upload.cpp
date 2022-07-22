#include <stdio.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fcntl.h>

#define URL "https://api-ap-singapore-1.getway.sinso.io/v1/upload?name=1.jpg"
#define CONTENT_TYPE_HEADER "Content-Type: image/jpg"
#define FILE_PATH "../java/src/main/java/io/sinso/upload/1.jpg"
#define TOKEN_HEADER "Token: <my-token>"

// compile via: g++ upload.cpp -o upload -lcurl

int main(void)
{
  CURL *curl;
  CURLcode res;
  struct stat file_info;
  curl_off_t speed_upload, total_time;
  FILE *fd;

  fd = fopen(FILE_PATH, "rb"); /* open file to upload */
  if(!fd)
    return 1; /* cannot continue */

  /* to get the file size */
  if(fstat(fileno(fd), &file_info) != 0)
    return 1; /* cannot continue */

  curl = curl_easy_init();

  struct curl_slist *list = NULL;

  if(curl) {
    /* upload to this place */
    curl_easy_setopt(curl, CURLOPT_URL, URL);

    list = curl_slist_append(list, CONTENT_TYPE_HEADER);
    list = curl_slist_append(list, TOKEN_HEADER);

    /* tell it to "upload" to the URL */
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    /* set where to read from (on Windows you need to use READFUNCTION too) */
    curl_easy_setopt(curl, CURLOPT_READDATA, fd);

    /* and give the size of the upload (optional) */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, file_info.st_size);

    /* enable verbose for easier tracing */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

    res = curl_easy_perform(curl);

    curl_slist_free_all(list);
    /* Check for errors */
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }
    else {
      /* now extract transfer info */
      curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD_T, &speed_upload);
      curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &total_time);

      fprintf(stderr, "Speed: %lu bytes/sec during %lu.%06lu seconds\n",
              (unsigned long)speed_upload,
              (unsigned long)(total_time / 1000000),
              (unsigned long)(total_time % 1000000));
    }
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  fclose(fd);
  return 0;
}
