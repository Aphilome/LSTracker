import { StrictMode } from 'react'
import { extendTheme } from '@chakra-ui/react'
import ReactDOM from "react-dom/client";
import App from './App.jsx'
import App_Tbirdper from './App_Tbirdper.jsx'
import App_Aphilome from './App_Aphilome.jsx'
import './index.css'
import {ChakraProvider} from "@chakra-ui/react";

const colors = {
    brand: {
        900: '#1a365d',
        800: '#153e75',
        700: '#2a69ac',
    },
}

const theme = extendTheme({ colors })

const rootElement =  document.getElementById('root');
const reactRoot = ReactDOM.createRoot(rootElement);

reactRoot.render(
  <StrictMode>
      <ChakraProvider theme={theme}>
          <App_Aphilome />
      </ChakraProvider>
  </StrictMode>,
)
