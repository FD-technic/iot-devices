#pragma once

class WiFiService {
    public:
        WiFiService(const char* ssid, const char* password);

        void connect();
        bool isConnected();
    private:
        const char* ssid;
        const char* password;
};