/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Aug 05 09:59:07 1999
 */
/* Compiler settings for D:\Projects\SDW V3\InterfaceContainer\InterfaceContainer.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __InterfaceContainer_h__
#define __InterfaceContainer_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISDWInterfaceContainer_FWD_DEFINED__
#define __ISDWInterfaceContainer_FWD_DEFINED__
typedef interface ISDWInterfaceContainer ISDWInterfaceContainer;
#endif 	/* __ISDWInterfaceContainer_FWD_DEFINED__ */


#ifndef __SDWInterfaceContainer_FWD_DEFINED__
#define __SDWInterfaceContainer_FWD_DEFINED__

#ifdef __cplusplus
typedef class SDWInterfaceContainer SDWInterfaceContainer;
#else
typedef struct SDWInterfaceContainer SDWInterfaceContainer;
#endif /* __cplusplus */

#endif 	/* __SDWInterfaceContainer_FWD_DEFINED__ */


/* header files for imported files */
#include "SDWConnector.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISDWInterfaceContainer_INTERFACE_DEFINED__
#define __ISDWInterfaceContainer_INTERFACE_DEFINED__

/* interface ISDWInterfaceContainer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISDWInterfaceContainer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("87E2B9B2-1993-11d3-A2BA-00801E00059A")
    ISDWInterfaceContainer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SDWNotify( 
            /* [in] */ long h,
            /* [in] */ long m) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWInitialise( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISDWInterfaceContainerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISDWInterfaceContainer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISDWInterfaceContainer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISDWInterfaceContainer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWNotify )( 
            ISDWInterfaceContainer __RPC_FAR * This,
            /* [in] */ long h,
            /* [in] */ long m);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWInitialise )( 
            ISDWInterfaceContainer __RPC_FAR * This);
        
        END_INTERFACE
    } ISDWInterfaceContainerVtbl;

    interface ISDWInterfaceContainer
    {
        CONST_VTBL struct ISDWInterfaceContainerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISDWInterfaceContainer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISDWInterfaceContainer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISDWInterfaceContainer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISDWInterfaceContainer_SDWNotify(This,h,m)	\
    (This)->lpVtbl -> SDWNotify(This,h,m)

#define ISDWInterfaceContainer_SDWInitialise(This)	\
    (This)->lpVtbl -> SDWInitialise(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISDWInterfaceContainer_SDWNotify_Proxy( 
    ISDWInterfaceContainer __RPC_FAR * This,
    /* [in] */ long h,
    /* [in] */ long m);


void __RPC_STUB ISDWInterfaceContainer_SDWNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWInterfaceContainer_SDWInitialise_Proxy( 
    ISDWInterfaceContainer __RPC_FAR * This);


void __RPC_STUB ISDWInterfaceContainer_SDWInitialise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISDWInterfaceContainer_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
