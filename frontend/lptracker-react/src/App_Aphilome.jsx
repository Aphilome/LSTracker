import Map from './components/Map'
import './App.css'
import Plot from 'react-plotly.js'
import {Box, Button} from "@chakra-ui/react"
import {DRONEPOSITIONSUWB, DRONEPOSITIONSGPS} from "./dronePositions";
import {useState} from "react";
import {ANCHORS} from "./anchors";
import PlotMain from "./components/PlotMain";



function App_Aphilome() {
    const [anchors, setAnchors] = useState(ANCHORS);
    const [dronePositionsUwb, setDronePositionsUwb] = useState(DRONEPOSITIONSUWB);
    const [dronePositionsGps, setDronePositionsGps] = useState(DRONEPOSITIONSGPS);

    return (
        <>
            <PlotMain dronePositionsUwb={dronePositionsUwb} dronePositionsGps={dronePositionsGps}/>
            <Map anchors={anchors} dronePositionsUwb={dronePositionsUwb} dronePositionsGps={dronePositionsGps} />
        </>
    )
}
export default App_Aphilome
