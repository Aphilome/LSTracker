import { StrictMode } from 'react'
import ReactDOM from "react-dom/client";
import App from './App.jsx'
import App_Tbirdper from './App_Tbirdper.jsx'
import './index.css'

const rootElement =  document.getElementById('root');
const reactRoot = ReactDOM.createRoot(rootElement);
reactRoot.render(
  <StrictMode>
    <App />
  </StrictMode>,
)
