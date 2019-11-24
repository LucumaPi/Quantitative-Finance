/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Aug 05 09:58:56 1999
 */
/* Compiler settings for D:\Projects\SDW V3\Interface\Interface.idl:
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

#ifndef __Interface_h__
#define __Interface_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISDWInterface_FWD_DEFINED__
#define __ISDWInterface_FWD_DEFINED__
typedef interface ISDWInterface ISDWInterface;
#endif 	/* __ISDWInterface_FWD_DEFINED__ */


#ifndef __SDWInterface_FWD_DEFINED__
#define __SDWInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class SDWInterface SDWInterface;
#else
typedef struct SDWInterface SDWInterface;
#endif /* __cplusplus */

#endif 	/* __SDWInterface_FWD_DEFINED__ */


/* header files for imported files */
#include "SDWConnector.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISDWInterface_INTERFACE_DEFINED__
#define __ISDWInterface_INTERFACE_DEFINED__

/* interface ISDWInterface */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISDWInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("343ABF10-038D-11d3-A29E-00801E00059A")
    ISDWInterface : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SDWInitialise( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWNotify( 
            /* [in] */ long h,
            /* [in] */ long m) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISDWInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISDWInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISDWInterface __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISDWInterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWInitialise )( 
            ISDWInterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWNotify )( 
            ISDWInterface __RPC_FAR * This,
            /* [in] */ long h,
            /* [in] */ long m);
        
        END_INTERFACE
    } ISDWInterfaceVtbl;

    interface ISDWInterface
    {
        CONST_VTBL struct ISDWInterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISDWInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISDWInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISDWInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISDWInterface_SDWInitialise(This)	\
    (This)->lpVtbl -> SDWInitialise(This)

#define ISDWInterface_SDWNotify(This,h,m)	\
    (This)->lpVtbl -> SDWNotify(This,h,m)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISDWInterface_SDWInitialise_Proxy( 
    ISDWInterface __RPC_FAR * This);


void __RPC_STUB ISDWInterface_SDWInitialise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWInterface_SDWNotify_Proxy( 
    ISDWInterface __RPC_FAR * This,
    /* [in] */ long h,
    /* [in] */ long m);


void __RPC_STUB ISDWInterface_SDWNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISDWInterface_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
