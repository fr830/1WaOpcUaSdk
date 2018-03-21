#pragma once
#include <stdint.h>
#include <string>
#include "opcua/Enums.h"
#include "opcua/Guid.h"
#include "opcua/ByteString.h"
#include "opcua/NumericNodeId.h"

namespace OWA {
  namespace OpcUa {
    union NodeIdIdentifier
    {
			NodeIdIdentifier() {};
			~NodeIdIdentifier() {};
      uint32_t      numericValue;
      std::string		stringValue;
      Guid					guidValue;
      ByteString		opaqueValue;
    };

    class NodeId 
    {
    public:
      NodeId();
			NodeId(const NodeId& other);
      NodeId(uint32_t id, uint16_t namespaceIndex = 0);
      NodeId(const std::string& id, uint16_t namespaceIndex = 0);
      NodeId(const Guid& id, uint16_t namespaceIndex = 0);
      NodeId(const ByteString& id, uint16_t namespaceIndex = 0);
			NodeId(Ids::NumericNodeId standardNumericNodeId);
			NodeId& operator=(const NodeId& other);
      bool operator==(const NodeId& other) const;
      virtual ~NodeId();

      inline uint16_t getNamespaceIndex() const {
        return namespaceIndex;
      };

			inline void setNamespaceIndex(const uint16_t newIndex = 0) {
				 namespaceIndex = newIndex;
			};
			
			inline IdentifierType getIdentifierType() const {
        return identifierType;
      }

      inline const NodeIdIdentifier& getIdentifier() const {
        return identifier;
      }
      void setNumericIdentifier(uint32_t id, uint16_t namespaceIndex = 0);
      void setStringIdentifier(const std::string& id, uint16_t namespaceIndex = 0);
      void setGuidIdentifier(const Guid& id, uint16_t namespaceIndex = 0);
      void setOpaqueIdentifier(const ByteString& id, uint16_t namespaceIndex = 0);
			std::string toString() const;
			
			bool parse(const std::string& valueAsString);
    
		protected:
      uint16_t          namespaceIndex;
      IdentifierType    identifierType;
      NodeIdIdentifier  identifier;

      void clear();
    };
  }
}