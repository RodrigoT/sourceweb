#ifndef INDEXER_INDEXERPPCALLBACKS_H
#define INDEXER_INDEXERPPCALLBACKS_H

#include <clang/Basic/SourceLocation.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/MacroInfo.h>
#include <clang/Lex/PPCallbacks.h>
#include <clang/Lex/Token.h>

namespace indexer {

class IndexerContext;

class IndexerPPCallbacks : public clang::PPCallbacks
{
public:
    IndexerPPCallbacks(IndexerContext &context) : m_context(context) {}

private:
    virtual void MacroExpands(const clang::Token &macroNameToken,
                              const clang::MacroInfo *mi,
                              clang::SourceRange range);
    virtual void MacroDefined(const clang::Token &macroNameToken,
                              const clang::MacroInfo *mi);
    virtual void Defined(const clang::Token &macroNameToken);
    virtual void Ifdef(clang::SourceLocation loc, const clang::Token &macroNameToken) { Defined(macroNameToken); }
    virtual void Ifndef(clang::SourceLocation loc, const clang::Token &macroNameToken) { Defined(macroNameToken); }

    void recordReference(const clang::Token &macroNameToken, const char *kind);

    IndexerContext &m_context;
};

} // namespace indexer

#endif // INDEXER_INDEXERPPCALLBACKS_H