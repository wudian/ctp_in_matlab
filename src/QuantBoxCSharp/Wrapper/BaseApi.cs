using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace QuantBoxCSharp.Callback
{
    public class BaseApi
    {
        private object locker = new object();

        public bool IsConnected { get; protected set; }

        protected fnOnConnect OnConnect_1;
        protected fnOnDisconnect OnDisconnect_1;
        protected fnOnRspError OnRspError_1;

        protected QuantBoxCSharp.fnOnConnect OnConnect_2;
        protected QuantBoxCSharp.fnOnDisconnect OnDisconnect_2;
        protected QuantBoxCSharp.fnOnRspError OnRspError_2;

        public BaseApi()
        {
            
        }

        ~BaseApi()
        {
         
        }

        public fnOnConnect OnConnect
        {
            set
            {
                OnConnect_1 = value;
                OnConnect_2 = OnConnect_3;
            }
        }

        protected virtual void OnConnect_3(ConnectionStatus result)
        {
            OnConnect_1(this, result);
        }

        public fnOnDisconnect OnDisconnect
        {
            set
            {
                OnDisconnect_1 = value;
                OnDisconnect_2 = OnDisconnect_3;
            }
        }
        protected virtual void OnDisconnect_3(ref CThostFtdcRspInfoField pRspInfo, ConnectionStatus step)
        {
            IsConnected = false;
            OnDisconnect_1(this, ref pRspInfo, step);
        }

        public fnOnRspError OnRspError
        {
            set
            {
                OnRspError_1 = value;
                OnRspError_2 = OnRspError_3;
            }
        }

        private void OnRspError_3(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
        {
            OnRspError_1(this, ref pRspInfo, nRequestID, bIsLast);
        }
    }
}
