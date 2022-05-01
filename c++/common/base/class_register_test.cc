// Author: txieyyue
// Date: 2022-05-01

#include "gtest/gtest.h"

#include "common/base/class_register.h"
#include "common/base/class_register_test.h"

class LocalFileImpl : public FileImpl {
  virtual std::string GetFileImplName() const { return "LocalFileImpl"; }
};
REGISTER_FILE_IMPL("/local", LocalFileImpl);

class MemFileImpl : public FileImpl {
  virtual std::string GetFileImplName() const { return "MemFileImpl"; }
};
REGISTER_FILE_IMPL("/mem", MemFileImpl);

class NetworkFileImpl : public FileImpl {
  virtual std::string GetFileImplName() const { return "NetworkFileImpl"; }
};
REGISTER_FILE_IMPL("/nfs", NetworkFileImpl);

TEST(ClassRegister, CreateFileImpl) {
  scoped_ptr<FileImpl> file_impl;
  file_impl.reset(CREATE_FILE_IMPL("/mem"));
  ASSERT_TRUE(file_impl.get() != NULL);
  EXPECT_EQ("MemFileImpl", file_impl->GetFileImplName());

  file_impl.reset(CREATE_FILE_IMPL("/nfs"));
  ASSERT_TRUE(file_impl.get() != NULL);
  EXPECT_EQ("NetworkFileImpl", file_impl->GetFileImplName());

  file_impl.reset(CREATE_FILE_IMPL("/local"));
  ASSERT_TRUE(file_impl.get() != NULL);
  EXPECT_EQ("LocalFileImpl", file_impl->GetFileImplName());

  file_impl.reset(CREATE_FILE_IMPL("/"));
  EXPECT_TRUE(file_impl.get() == NULL);

  file_impl.reset(CREATE_FILE_IMPL(""));
  EXPECT_TRUE(file_impl.get() == NULL);

  file_impl.reset(CREATE_FILE_IMPL("/mem2"));
  EXPECT_TRUE(file_impl.get() == NULL);

  file_impl.reset(CREATE_FILE_IMPL("/mem/"));
  EXPECT_TRUE(file_impl.get() == NULL);

  file_impl.reset(CREATE_FILE_IMPL("/nfs2/"));
  EXPECT_TRUE(file_impl.get() == NULL);
}

TEST(ClassRegister, FileImplNames) {
  EXPECT_EQ(3u, FILE_IMPL_COUNT());

  std::set<std::string> file_impl_names;
  for (size_t i = 0; i < FILE_IMPL_COUNT(); ++i) {
    file_impl_names.insert(FILE_IMPL_NAME(i));
  }
  EXPECT_EQ(3u, file_impl_names.size());
  EXPECT_TRUE(file_impl_names.find("/mem") != file_impl_names.end());
  EXPECT_TRUE(file_impl_names.find("/nfs") != file_impl_names.end());
  EXPECT_TRUE(file_impl_names.find("/local") != file_impl_names.end());
}

TEST(ClassRegister, FileImplSingleton) {
  scoped_ptr<FileImpl> file_impl;
  ASSERT_TRUE(GET_FILE_IMPL_SINGLETON("/mem") != NULL);
  EXPECT_EQ("MemFileImpl", GET_FILE_IMPL_SINGLETON("/mem")->GetFileImplName());
  // Test if it's a "real" singleton.
  EXPECT_EQ(GET_FILE_IMPL_SINGLETON("/mem"), GET_FILE_IMPL_SINGLETON("/mem"));
  file_impl.reset(CREATE_FILE_IMPL("/mem"));
  EXPECT_NE(GET_FILE_IMPL_SINGLETON("/mem"), file_impl.get());

  ASSERT_TRUE(GET_FILE_IMPL_SINGLETON("/nfs") != NULL);
  EXPECT_EQ("NetworkFileImpl",
            GET_FILE_IMPL_SINGLETON("/nfs")->GetFileImplName());
  EXPECT_EQ(GET_FILE_IMPL_SINGLETON("/nfs"), GET_FILE_IMPL_SINGLETON("/nfs"));
  file_impl.reset(CREATE_FILE_IMPL("/nfs"));
  EXPECT_NE(GET_FILE_IMPL_SINGLETON("/nfs"), file_impl.get());

  ASSERT_TRUE(GET_FILE_IMPL_SINGLETON("/local") != NULL);
  EXPECT_EQ("LocalFileImpl",
            GET_FILE_IMPL_SINGLETON("/local")->GetFileImplName());
  EXPECT_EQ(GET_FILE_IMPL_SINGLETON("/local"),
            GET_FILE_IMPL_SINGLETON("/local"));
  file_impl.reset(CREATE_FILE_IMPL("/local"));
  EXPECT_NE(GET_FILE_IMPL_SINGLETON("/local"), file_impl.get());

  EXPECT_TRUE(GET_FILE_IMPL_SINGLETON("/") == NULL);
  EXPECT_TRUE(GET_FILE_IMPL_SINGLETON("") == NULL);
  EXPECT_TRUE(GET_FILE_IMPL_SINGLETON("/mem/") == NULL);
  EXPECT_TRUE(GET_FILE_IMPL_SINGLETON("/mem2") == NULL);
}
