#ifndef IO_I_DOCUMENT_IO_H
#define IO_I_DOCUMENT_IO_H

#include "model/document.h"

#include <string>

namespace editor {
namespace io {

class IDocumentIO {
public:
    virtual ~IDocumentIO() = default;

    virtual bool importDocument(const std::string& path, model::Document& document) const = 0;
    virtual bool exportDocument(const model::Document& document, const std::string& path) const = 0;
};

}  // namespace io
}  // namespace editor

#endif  // IO_I_DOCUMENT_IO_H
