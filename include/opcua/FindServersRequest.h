#pragma once
#include "opcua/RequestHeader.h"
#include <boost/any.hpp>

namespace OWA {
  namespace OpcUa {
    struct  FindServersRequest {
      static RequestResponseTypeId getTypeId() {
        return RequestResponseTypeId::FindServersRequest;
      }
      RequestHeader header;
			boost::any		context;
      std::string endpointUrl;
      std::vector<std::string> localeIds;
      std::vector<std::string> serverUris;

			typedef std::shared_ptr<FindServersRequest> Ptr;
    };
  }
}