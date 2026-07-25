#pragma once

class WifiService {
    public:
        void init();
        void connect();
        bool isConnected();
};