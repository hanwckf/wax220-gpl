#ifndef __UTIL_AST_H__
#define __UTIL_AST_H__

#define UTIL_Assert(cond)

/*!\file util_ast.h
 * \brief Header file for assert functions.
 *  
 *  For production builds, define NDEBUG to disable asserts.
 */

/** Check that an assumed condition is TRUE.
 * 
 * This should be used during development only.  For production code,
 * compile with NDEBUG defined.
 */
#define utilAst_assert(expr) utilAst_assertFunc(__FILE__, __LINE__, __STRING(expr), (expr))

/** The actual assert function, don't call this directly, use the macro.
 *
 * @param filename (IN) file where the assert occured.
 * @param lineNumber (IN) Linenumber of the assert statement.
 * @param exprString (IN) The actual expression that is being asserted.
 * @param expr       (IN) The result of the evaluation of the expression.  0 is fail,
 *                        non-zero is pass.
 */
void utilAst_assertFunc(const char *filename, UINT32 lineNumber, const char *exprString, SINT32 expr);

#endif /* __UTIL_AST_H__ */
