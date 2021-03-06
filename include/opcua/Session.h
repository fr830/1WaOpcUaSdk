#pragma once

#include "opcua/RequestHeader.h"
#include "opcua/ResponseHeader.h"
#include "opcua/Enums.h"
#include "opcua/Utils.h"

#include "opcua/ApplicationDescription.h"
#include "opcua/SecurityPolicy.h"
#include "opcua/GetEndpoints.h"
#include "opcua/UserIdentityToken.h"

namespace OWA {
  namespace OpcUa {
    typedef NodeId SessionAuthenticatonToken;
    struct SignatureData {
      std::string algorithm;
      ByteString signature;
    };

    struct CreateSessionRequest {
      CreateSessionRequest();

      static RequestResponseTypeId getTypeId() {
        return RequestResponseTypeId::CreateSessionRequest;
      }
      RequestHeader header;
      ApplicationDescription clientDescription;
      std::string serverUri;
      std::string endpointUrl;
      std::string sessionName;
      SecureByteString clientNonce;
      ByteString clientCertificate;
      Duration requestedSessionTimeout;
      uint32_t maxResponseMessageSize;

			typedef std::shared_ptr<CreateSessionRequest> Ptr;
    };

    struct CreateSessionResponse {
      ResponseHeader header;
      NodeId sessionId;
      SessionAuthenticatonToken authenticationToken;
      Duration revisedSessionTimeout;
      SecureByteString serverNonce;
      ByteString serverCertificate;
      std::vector<EndpointDescription> serverEndpoints;
      std::vector<ByteString> serverSoftwareCertificates;
      SignatureData signatureData;
      uint32_t maxRequestMessageSize;
    };

    struct ActivateSessionRequest {
      ActivateSessionRequest();
      static RequestResponseTypeId getTypeId() {
        return RequestResponseTypeId::ActivateSessionRequest;
      }
      RequestHeader header;
      SignatureData clientSignature;
      std::vector<ByteString> clientSoftwareCertificates;
      std::vector<std::string> localeIds;
      ExtensionObject::Ptr userIdentityToken;
      SignatureData userTokenSignature;

			typedef std::shared_ptr<ActivateSessionRequest> Ptr;
    };

    struct ActivateSessionResponse {
      ResponseHeader header;
      SecureByteString serverNonce;
      std::vector<StatusCode> results;
      std::vector<DiagnosticInfo> diagnosticInfos;
			inline bool isGood() { return StatusCodeUtil::isGood(this->header.serviceResult); }
    };
  }
}