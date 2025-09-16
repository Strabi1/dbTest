#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <curl/curl.h>

struct httpResponseData
{
	size_t size;
	char *data;
};

size_t curl_write_data(void *ptr, size_t size, size_t nmemb, void *userData) {
    struct httpResponseData *data = (struct httpResponseData *)userData;

    size_t index = data->size;
    size_t n = (size * nmemb);
    char* tmp;

    data->size += (size * nmemb);
    tmp = (char *)realloc(data->data, data->size + 1); /* +1 for '\0' */

    if(tmp) {
        data->data = tmp;
    } else {
        if(data->data) {
            free(data->data);
        }
        return 0;
    }

    memcpy((data->data + index), ptr, n);
    data->data[data->size] = '\0';

    return size * nmemb;
}

int main(int argc, char *argv[])
{
	CURL *curl = curl_easy_init();
	struct httpResponseData response;

	if (curl)
	{
		// Setup curl
		curl_easy_setopt(curl, CURLOPT_URL, "127.0.0.1.8080/apis/food");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		// Start Query
		CURLcode res = curl_easy_perform(curl);
		if (res == CURLE_OK)
		{
			printf("response: %s", response.data);
		}

		curl_easy_cleanup(curl);
	}

	if (response.data)
		free(response.data);
}