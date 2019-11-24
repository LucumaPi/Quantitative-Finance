/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Aug 05 09:58:38 1999
 */
/* Compiler settings for D:\Projects\SDW V3\Display\Display.idl:
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

#ifndef __Display_h__
#define __Display_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISDWDisplay_FWD_DEFINED__
#define __ISDWDisplay_FWD_DEFINED__
typedef interface ISDWDisplay ISDWDisplay;
#endif 	/* __ISDWDisplay_FWD_DEFINED__ */


#ifndef __SDWDisplay_FWD_DEFINED__
#define __SDWDisplay_FWD_DEFINED__

#ifdef __cplusplus
typedef class SDWDisplay SDWDisplay;
#else
typedef struct SDWDisplay SDWDisplay;
#endif /* __cplusplus */

#endif 	/* __SDWDisplay_FWD_DEFINED__ */


/* header files for imported files */
#include "SDWConnector.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISDWDisplay_INTERFACE_DEFINED__
#define __ISDWDisplay_INTERFACE_DEFINED__

/* interface ISDWDisplay */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISDWDisplay;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ACA4AA41-03BC-11d3-A29E-00801E00059A")
    ISDWDisplay : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SDWDisplayTime( 
            /* [in] */ long h,
            /* [in] */ long m) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISDWDisplayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISDWDisplay __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISDWDisplay __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISDWDisplay __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWDisplayTime )( 
            ISDWDisplay __RPC_FAR * This,
            /* [in] */ long h,
            /* [in] */ long m);
        
        END_INTERFACE
    } ISDWDisplayVtbl;

    interface ISDWDisplay
    {
        CONST_VTBL struct ISDWDisplayVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISDWDisplay_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISDWDisplay_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISDWDisplay_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISDWDisplay_SDWDisplayTime(This,h,m)	\
    (This)->lpVtbl -> SDWDisplayTime(This,h,m)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISDWDisplay_SDWDisplayTime_Proxy( 
    ISDWDisplay __RPC_FAR * This,
    /* [in] */ long h,
    /* [in] */ long m);


void __RPC_STUB ISDWDisplay_SDWDisplayTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISDWDisplay_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
