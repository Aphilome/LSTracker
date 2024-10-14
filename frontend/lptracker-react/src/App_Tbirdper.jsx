import {useState} from "react";
import axios from "axios";

function App_Tbirdper() {
    const baseUri = 'http://localhost:5298';
    const [port, setPort] = useState('com8');
    const [message, setMessage] = useState('');

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
    const onClose = () => {
        axios.delete(`${baseUri}/close`)
            .then(r => {

            })
            .catch(e => alert(e));
    }

    return (
        <>
            <input type={'text'} value={port} onChange={e => setPort(e.target.value)}/>
            <button onClick={onOpen}>Open</button>
            <br/>
            <input type={'text'} value={message} onChange={e => setMessage(e.target.value)}/>
            <button onClick={onSend}>Send</button>
            <br/>
            <button onClick={onClose}>Close</button>

        </>
    )
}

export default App_Tbirdper