// Author: txieyyue
// Date: 2022-05-01

#ifndef COMMON_BASE_CLASS_REGISTER_TEST_H_
#define COMMON_BASE_CLASS_REGISTER_TEST_H_

#include "common/base/class_register.h"

class FileImpl {
public:
    FileImpl() {}
    virtual ~FileImpl() {}

    virtual std::string GetFileImplName() const = 0;
};

CLASS_REGISTER_DEFINE_REGISTRY(file_impl_register, FileImpl);

#define REGISTER_FILE_IMPL(path_prefix_as_string, file_impl_name) \
    CLASS_REGISTER_OBJECT_CREATOR_WITH_SINGLETON( \
        file_impl_register, FileImpl, path_prefix_as_string, file_impl_name)

#define CREATE_FILE_IMPL(path_prefix_as_string) \
    CLASS_REGISTER_CREATE_OBJECT(file_impl_register, path_prefix_as_string)

#define GET_FILE_IMPL_SINGLETON(path_prefix_as_string) \
    CLASS_REGISTER_GET_SINGLETON(file_impl_register, path_prefix_as_string)

#define FILE_IMPL_COUNT() \
    CLASS_REGISTER_CREATOR_COUNT(file_impl_register)

#define FILE_IMPL_NAME(i) \
    CLASS_REGISTER_CREATOR_NAME(file_impl_register, i)

#endif // COMMON_BASE_CLASS_REGISTER_TEST_H_
