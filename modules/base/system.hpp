#ifndef __SYSTEM_ADAPTER_H__
#define __SYSTEM_ADAPTER_H__

#ifdef __unix__
#include <sys/time.h>
#include <sys/syscall.h>
#include <unistd.h>
#else
#include <Windows.h>
#endif


namespace sys {

long gettid()
{
#ifdef __unix__
    return syscall(SYS_gettid);
#else
    DWORD thread_id = GetCurrentThreadId();
    return static_cast<long>(thread_id);
#endif
}

} // namespace sys

#endif // __SYSTEM_ADAPTER_H__