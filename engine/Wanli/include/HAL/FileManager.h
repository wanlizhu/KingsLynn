#pragma once

#include "BasicTypes.h"
#include "HAL/File.h"
#include "Utilities/NonCopyable.h"

#ifdef CreateFile
#undef CreateFile
#endif

namespace Wanli
{
    class DLLDECL FileManager : public NonCopyable
    {
    public:
        static FileManager* Get();

        void AddSearchPath(const Path& path);
        void RemoveSearchPath(const Path& path);
        void ClearSearchPaths();
        SharedPtr<StringArray> GetSearchPaths() const;

        bool Exists(const String& name) const;
        bool Delete(const String& name) const;

        SharedPtr<File> CreateFile(const String& name);
        SharedPtr<StringArray> EnumerateFiles(const String& name, bool recursive = false) const;
    
    protected:
        FileManager();
        virtual ~FileManager();
    };
}