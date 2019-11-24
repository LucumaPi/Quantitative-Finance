/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Aug 05 10:00:08 1999
 */
/* Compiler settings for D:\Projects\SDW V3\Panel\Panel.idl:
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

#ifndef __Panel_h__
#define __Panel_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISDWPanel_FWD_DEFINED__
#define __ISDWPanel_FWD_DEFINED__
typedef interface ISDWPanel ISDWPanel;
#endif 	/* __ISDWPanel_FWD_DEFINED__ */


#ifndef __SDWPanel_FWD_DEFINED__
#define __SDWPanel_FWD_DEFINED__

#ifdef __cplusplus
typedef class SDWPanel SDWPanel;
#else
typedef struct SDWPanel SDWPanel;
#endif /* __cplusplus */

#endif 	/* __SDWPanel_FWD_DEFINED__ */


/* header files for imported files */
#include "sdwconnector.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISDWPanel_INTERFACE_DEFINED__
#define __ISDWPanel_INTERFACE_DEFINED__

/* interface ISDWPanel */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISDWPanel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("737DD121-03B4-11d3-A29E-00801E00059A")
    ISDWPanel : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SDWA( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWB( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SDWState( 
            /* [out] */ unsigned char __RPC_FAR *state) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISDWPanelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISDWPanel __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISDWPanel __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISDWPanel __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWA )( 
            ISDWPanel __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWB )( 
            ISDWPanel __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SDWState )( 
            ISDWPanel __RPC_FAR * This,
            /* [out] */ unsigned char __RPC_FAR *state);
        
        END_INTERFACE
    } ISDWPanelVtbl;

    interface ISDWPanel
    {
        CONST_VTBL struct ISDWPanelVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISDWPanel_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISDWPanel_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISDWPanel_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISDWPanel_SDWA(This)	\
    (This)->lpVtbl -> SDWA(This)

#define ISDWPanel_SDWB(This)	\
    (This)->lpVtbl -> SDWB(This)

#define ISDWPanel_SDWState(This,state)	\
    (This)->lpVtbl -> SDWState(This,state)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISDWPanel_SDWA_Proxy( 
    ISDWPanel __RPC_FAR * This);


void __RPC_STUB ISDWPanel_SDWA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWPanel_SDWB_Proxy( 
    ISDWPanel __RPC_FAR * This);


void __RPC_STUB ISDWPanel_SDWB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISDWPanel_SDWState_Proxy( 
    ISDWPanel __RPC_FAR * This,
    /* [out] */ unsigned char __RPC_FAR *state);


void __RPC_STUB ISDWPanel_SDWState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISDWPanel_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
