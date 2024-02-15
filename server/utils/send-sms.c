#include <stdio.h>
// https://curl.se/libcurl/
#include <curl/curl.h>
// also need cjson
#include <cjson/cJSON.h>

int main(void)
{
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        struct curl_slist *chunk = NULL;

        // Authentication with Twilio API
        curl_easy_setopt(curl, CURLOPT_USERNAME, ""); // Twilio Account SID
        curl_easy_setopt(curl, CURLOPT_PASSWORD, ""); // Twilio Auth Token

        // Twilio API URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.twilio.com/2010-04-01/Accounts/TWILIO_ACCOUNT_SID/Messages.json");

        // Add the headers
        chunk = curl_slist_append(chunk, "Content-Type: application/x-www-form-urlencoded");

        // Set the POST fields
        char postfields[256];
        sprintf(postfields, "To=+1234567890&From=+1234567890&Body=Hello from C");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields);

        // Set the custom headers
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // Clean up
        curl_easy_cleanup(curl);

        // Free the custom headers
        curl_slist_free_all(chunk);
    }

    curl_global_cleanup();
    return 0;
}
