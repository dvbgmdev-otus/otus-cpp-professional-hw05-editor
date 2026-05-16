#ifndef IO_FILE_DOCUMENT_IO_H
#define IO_FILE_DOCUMENT_IO_H

#include "io/i_document_io.h"

namespace editor {
namespace io {

class FileDocumentIO final : public IDocumentIO {
public:
    bool importDocument(const std::string& path, model::Document& document) const override;
    bool exportDocument(const model::Document& document, const std::string& path) const override;
};

}  // namespace io
}  // namespace editor

#endif  // IO_FILE_DOCUMENT_IO_H
