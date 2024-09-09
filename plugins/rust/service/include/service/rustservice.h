#ifndef CC_SERVICE_RUST_RUSTSSERVICE_H
#define CC_SERVICE_RUST_RUSTSSERVICE_H

#include <memory>
#include <vector>

#include <boost/program_options/variables_map.hpp>

#include <odb/database.hxx>
#include <util/odbtransaction.h>
#include <webserver/servercontext.h>

#include <RustService.h>

namespace cc
{
namespace service
{
namespace rust
{

class RustServiceHandler : virtual public RustServiceIf
{
public:
  RustServiceHandler(
    std::shared_ptr<odb::database> db_,
    std::shared_ptr<std::string> datadir_,
    const cc::webserver::ServerContext& context_);

  void getFileTypes(std::vector<std::string>& return_) override;

  void getRustString(std::string& str_);

private:
  std::shared_ptr<odb::database> _db;
  util::OdbTransaction _transaction;

  const boost::program_options::variables_map& _config;
};

} // rust
} // service
} // cc

#endif // CC_SERVICE_RUST_RUSTSSERVICE_H
