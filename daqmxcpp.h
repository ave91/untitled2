#pragma once

/** @file daqmxcpp.h
 ** @author R Benjamin Voigt (richardvoigt@gmail.com)
 **
 ** Rights reserved.  This code is not public domain.
 **
 ** Licensed under CC BY-SA 3.0             http://creativecommons.org/licenses/by-sa/3.0/
 **             or Lesser GPL 3 or later    http://www.gnu.org/copyleft/lesser.html
 ** with the following restrictions (per GPL section 7):
 **  - all warranties are disclaimed, and if this is prohibited by law, your sole remedy shall be recovery of the price you paid to receive the code
 **  - derived works must not remove this license notice or author attribution
 **  - modifications must not be represented as the work of the original author
 **  - attribution is required in the "about" or "--version" display of any work linked hereto, or wherever copyright notices are displayed by the composite work
 **/

#include <string>

namespace NIDAQmx
{
    namespace innards
    {
        extern "C" {
#include <NIDAQmx.h>
#pragma comment(linker, "/DEFAULTLIB:nidaqmx-32.lib")
        }
    }

    class DAQException : public std::exception
    {
        const innards::int32 m_code;

        DAQException& operator=(const DAQException&);
    public:
        DAQException(innards::int32 errorCode)
            : exception("exception in NI-DAQmx library")
            , m_code(errorCode)
        {
        }

        int code() const { return m_code; }
        std::string description() const
        {
            std::string buffer;
            innards::int32 neededSize = innards::DAQmxGetErrorString(m_code, NULL, 0);
            if (neededSize > 0) {
                buffer.resize(neededSize);
                innards::DAQmxGetErrorString(m_code, &buffer[0], neededSize);
            }
            return buffer;
        }
    };

    class Task sealed
    {
        typedef innards::TaskHandle TaskHandle;
        const TaskHandle m_handle;

        Task(TaskHandle handle)
            : m_handle(handle)
        {
        }

        TaskHandle CreateNamedTask(std::string name)
        {
            TaskHandle retval;
            innards::int32 error = innards::DAQmxCreateTask(name.c_str(), &retval);
            if (error < 0)
                throw DAQException(error);

            return retval;
        }

        Task& operator=(const Task&);   // not provided
    public:
        Task(std::string name)
            : m_handle(CreateNamedTask(name))
        {
        }

        ~Task()
        {
            innards::DAQmxClearTask(m_handle);
        }

        void AddChannel(std::string physicalName, int terminalConfig, double minVal, double maxVal, std::string customScale = std::string())
        {
            innards::int32 error = innards::DAQmxCreateAIVoltageChan(m_handle, physicalName.c_str(), NULL, terminalConfig, minVal, maxVal, customScale.empty()? DAQmx_Val_Volts: DAQmx_Val_Custom, customScale.empty()? NULL: customScale.c_str());
            if (error < 0)
                throw DAQException(error);
        }

        size_t GetChannelCount( void ) const
        {
            innards::uInt32 chanCount;
            innards::int32 error = innards::DAQmxGetTaskNumChans(m_handle, &chanCount);
            if (error < 0)
                throw DAQException(error);
            return chanCount;
        }

        void SetupContinuousAcquisition(double samplesPerSecond, unsigned int bufferSize)
        {
            innards::int32 error = innards::DAQmxCfgSampClkTiming(m_handle, NULL, samplesPerSecond, DAQmx_Val_Rising, DAQmx_Val_ContSamps, bufferSize);
            if (error < 0)
                throw DAQException(error);
        }

        void Start()
        {
            innards::int32 error = innards::DAQmxStartTask(m_handle);
            if (error < 0)
                throw DAQException(error);
        }

        void Stop()
        {
            innards::int32 error = innards::DAQmxStopTask(m_handle);
            if (error < 0)
                throw DAQException(error);
        }

        size_t TryRead(double buffer[], size_t bufferSize, innards::bool32 fillMode = DAQmx_Val_GroupByScanNumber)
        {
            innards::int32 truncatedBufferSize = (innards::int32)bufferSize;
            if (truncatedBufferSize < 0 || bufferSize != (size_t)truncatedBufferSize)
                throw "invalid bufferSize";
            innards::int32 samplesRead;
            innards::int32 error = innards::DAQmxReadAnalogF64(m_handle, DAQmx_Val_Auto, 0, fillMode, buffer, truncatedBufferSize, &samplesRead, NULL);
            if (error < 0)
                throw DAQException(error);
            return samplesRead;
        }

        void SyncReadNonInterleaved(double buffer[], size_t bufferSize, size_t samplesToRead)
        {
            innards::int32 truncatedBufferSize = (innards::int32)bufferSize;
            if (truncatedBufferSize < 0 || bufferSize != (size_t)truncatedBufferSize)
                throw "invalid bufferSize";
            innards::int32 truncatedSamplesToRead = (innards::int32)samplesToRead;
            if (truncatedSamplesToRead < 0 || samplesToRead != (size_t)truncatedSamplesToRead)
                throw "invalid samplesToRead";
            innards::int32 samplesRead;
            innards::int32 error = innards::DAQmxReadAnalogF64(m_handle, truncatedSamplesToRead, -1, DAQmx_Val_GroupByChannel, buffer, truncatedBufferSize, &samplesRead, NULL);
            if (error < 0)
                throw DAQException(error);
            if (samplesRead != truncatedSamplesToRead)
                throw "DAQmxReadAnalogF64 misbehaved?";
        }

        template<size_t N>
        size_t TryRead(double (&buffer)[N])
        {
            return TryRead(buffer, N, DAQmx_Val_GroupByScanNumber);
        }

        template<size_t N>
        size_t TryReadNonInterleaved(double (&buffer)[N])
        {
            return TryRead(buffer, N, DAQmx_Val_GroupByChannel);
        }

        template<size_t N>
        void SyncReadNonInterleaved(double (&buffer)[N], size_t samplesToRead)
        {
            SyncReadNonInterleaved(buffer, N, samplesToRead);
        }

        template<size_t N>
        void SyncReadTimeout(double (&buffer)[N], size_t samplesToRead, double secondsTimeout)
        {
            innards::int32 truncatedBufferSize = (innards::int32)N;
            if (truncatedBufferSize < 0 || N != (size_t)truncatedBufferSize)
                throw "invalid bufferSize";
            innards::int32 truncatedSamplesToRead = (innards::int32)samplesToRead;
            if (truncatedSamplesToRead < 0 || samplesToRead != (size_t)truncatedSamplesToRead)
                throw "invalid samplesToRead";
            innards::int32 samplesRead;
            innards::int32 error = innards::DAQmxReadAnalogF64(m_handle, truncatedSamplesToRead, secondsTimeout, DAQmx_Val_GroupByScanNumber, buffer, truncatedBufferSize, &samplesRead, NULL);
            if (error < 0)
                throw DAQException(error);
            if (samplesRead != truncatedSamplesToRead)
                throw "DAQmxReadAnalogF64 misbehaved?";
        }

        template<typename TFunctor>
        void* SubscribeSamplesRead(unsigned int blockSize, TFunctor* callbackFunctor)
        {
            struct ReadSamplesRegistration
            {
                Task* const m_pTask;
                TFunctor* const m_functor;
                static innards::int32 CVICALLBACK Callback(innards::TaskHandle taskHandle, innards::int32, innards::uInt32 /*nSamples*/, void* pCallbackData)
                {
                    ReadSamplesRegistration* that = static_cast<ReadSamplesRegistration*>(pCallbackData);
                    if (that->m_pTask->m_handle != taskHandle)
                        return -1;

                    return (*that->m_functor)(that->m_pTask);

                }

                ReadSamplesRegistration(Task* pTask, TFunctor* callbackFunctor)
                    : m_pTask(pTask)
                    , m_functor(callbackFunctor)
                {
                }

            private:
                ReadSamplesRegistration& operator=(const ReadSamplesRegistration&) { __assume(false); }
            }* pRegistration = new ReadSamplesRegistration(this, callbackFunctor);

            innards::int32 error = innards::DAQmxRegisterEveryNSamplesEvent(m_handle, DAQmx_Val_Acquired_Into_Buffer, blockSize, 0, &ReadSamplesRegistration::Callback, pRegistration);
            if (error < 0)
                throw DAQException(error);

            return pRegistration;
        }
    };
}
