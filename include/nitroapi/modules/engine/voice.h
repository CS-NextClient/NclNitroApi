#pragma once

namespace nitroapi
{
    class VoiceRecordInterface
    {
    public:
        virtual ~VoiceRecordInterface() = 0;
        virtual void Unknown() = 0;
        virtual void RecordStart() = 0;
        virtual void RecordStop() = 0;
        virtual void UpdateVoice() = 0;

        // returns samples num in 16 bit format
        virtual int GetRecordedData(char *pOut, int nSamplesWanted) = 0;
    };
}