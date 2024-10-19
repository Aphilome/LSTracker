import {useEffect, useState} from "react";
import axios from "axios";
import './App.css'

function App_Tbirdper() {
    const testReceiveAnc = 'anc~01_12.12345678_23.12345678_34.12345678_-50_2024-01-01T16-28-12~02_12.345678_23.456789_34.567890_777_2024-01-01T16-28-12~03_12.345678_23.456789_34.567890_777_2024-01-01T16-28-12';
    const testReceivePos = 'pos~12.345678_23.456789_34.567890_0_2024-01-01T16-28-12~12.345678_23.456789_34.567890_-777_2024-01-01T16-28-12';

    const baseUri = 'http://localhost:5298';
    const [port, setPort] = useState('com8');
    const [message, setMessage] = useState('');
    const [receiveMessage, setReceiveMessage] = useState(testReceivePos);
    const [anchors, setAnchors] = useState([]);
    const [logs, setLogs] = useState([]);
    const [uwbPositions, setUwbPositions] = useState([]);
    const [gpsPositions, setGpsPositions] = useState([]);

    useEffect(() => {
        axios.get(`${baseUri}/anchors`)
            .then(r => {
                setAnchors(r.data);
            })
            .catch(e => alert(e));
        axios.get(`${baseUri}/logs`)
            .then(r => {
                setLogs(r.data);
            })
            .catch(e => alert(e));
        axios.get(`${baseUri}/uwb`)
            .then(r => {
                setUwbPositions(r.data);
            })
            .catch(e => alert(e));
        axios.get(`${baseUri}/uwb`)
            .then(r => {
                setUwbPositions(r.data);
            })
            .catch(e => alert(e));
        axios.get(`${baseUri}/gps`)
            .then(r => {
                setGpsPositions(r.data);
            })
            .catch(e => alert(e));
    }, []);

    const onOpen = () => {
        axios.post(`${baseUri}/open?portName=${port}`)
            .then(r => {

            })
            .catch(e => alert(e));
    }

    const onSend = () => {
        axios.put(`${baseUri}/send?msg=${message}`)
            .then(r => {

            })
            .catch(e => alert(e));
    }
    const onReceiveTest = () => {
        axios.get(`${baseUri}/receive-test?msg=${receiveMessage}`)
            .then(r => {

            })
            .catch(e => alert(e));
    }

    const onClose = () => {
        axios.delete(`${baseUri}/close`)
            .then(r => {

            })
            .catch(e => alert(e));
    }

    return (
        <>
            <div className="flex flex-row">
                <div className="controls flex-1">
                    <div>
                        <input className="rounded-md border-0 py-1.5 text-gray-900 shadow-sm ring-1 ring-inset ring-gray-300 placeholder:text-gray-400 focus:ring-2 focus:ring-inset focus:ring-indigo-600" type={'text'} value={port} onChange={e => setPort(e.target.value)}/>
                        <button className="bg-blue-400 rounded-2xl p-1 px-3" onClick={onOpen}>Open</button>
                    </div>
                    <div>
                        <input className="rounded-md border-0 py-1.5 text-gray-900 shadow-sm ring-1 ring-inset ring-gray-300 placeholder:text-gray-400 focus:ring-2 focus:ring-inset focus:ring-indigo-600" type={'text'} value={message} onChange={e => setMessage(e.target.value)}/>
                        <button className="bg-blue-400 rounded-2xl p-1 px-3" onClick={onSend}>Send</button>
                    </div>
                    <div >
                        <input className="rounded-md border-0 py-1.5 text-gray-900 shadow-sm ring-1 ring-inset ring-gray-300 placeholder:text-gray-400 focus:ring-2 focus:ring-inset focus:ring-indigo-600" type={'text'} value={receiveMessage} onChange={e => setReceiveMessage(e.target.value)}/>
                        <button className="bg-blue-400 rounded-2xl p-1 px-3" onClick={onReceiveTest}>Test receive</button>
                    </div>
                    <button className="bg-blue-400 rounded-2xl p-1 px-3" onClick={onClose}>Close</button>
                    <div className="logs bg-lime-700">
                        <label className="block text-center font-bold">Logs</label>
                        {
                            logs.map((e, i) => <label key={i} className="block text-left m-1 text-xs">#{i + 1} {e}</label>)
                        }
                    </div>
                </div>


                <div className="datas flex-1">
                     <div className="bg-amber-600">
                         <label className="block text-center font-bold">Anchors (lat, lon, alt, signal)</label>
                         {
                             anchors.map((e, i) => (<label key={i} className="block text-left text-xs">{`[${e.name}] ${e.latitude}, ${e.longitude} ${e.altitude} (${e.signalLevel}db) ${e.lastTime}`}</label>))
                         }
                     </div>
                    <div className="flex flex-row">
                        <div className="flex-1 bg-indigo-600">
                            <label className="block text-center font-bold">UWB</label>
                            {
                                uwbPositions.map((e, i) => (<label key={i} className="block text-left text-xs">{`${e.latitude}, ${e.longitude} ${e.altitude} (${e.signalLevel}db) ${e.time}`}</label>))
                            }
                        </div>
                        <div className="flex-1 bg-green-200">
                            <label className="block text-center font-bold">GPS</label>
                            {
                                gpsPositions.map((e, i) => (<label key={i} className="block text-left text-xs">{`${e.latitude}, ${e.longitude} ${e.altitude} (${e.signalLevel}db) ${e.time}`}</label>))
                            }
                        </div>
                    </div>
                </div>
            </div>
        </>
    )
}

export default App_Tbirdper