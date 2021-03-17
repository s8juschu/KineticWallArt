#ifndef DEBUG_H
#define DEBUG_H

#include "Connection.h"

extern String debug_topic;

class DebugClass {
    public:
        void print(String str);
        void print(char c);
        void println(String str);
        void println(char c);
        template<typename ... Args>
        void printf( const char* format, Args ... args )
        {
            Serial.printf(format, args...);
            int size = snprintf( nullptr, 0, format, args ... ) + 1;
            if( size <= 0 ){ return; }
            char buf[size]; 
            snprintf( buf, size, format, args ... );
            Connection.send(debug_topic, String(buf));
        }
};

extern DebugClass Debug;
#endif