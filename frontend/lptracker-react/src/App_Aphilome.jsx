import Map from './components/Map'
import './App.css'
import Plot from 'react-plotly.js'
import {DRONEPOSITIONSGPS} from "./dronePositions";
import { Box } from "@chakra-ui/react"

function randomValues(num, mul) {
    const arr = [];
    const index = [];
    for (let i = 0; i < num; i++) {
        arr.push(Math.random() * mul)
        index.push(i);
    }
    return {index, arr};
}

function App_Aphilome() {
    const traces = Array(3).fill(0).map((_, i) => {
        const {index, arr} = randomValues(20, 3);
        return {
            x: Array(20).fill(i),
            y: index,
            z: arr,
            type: 'scatter3d',
            mode: 'lines'
        }
    });

    return (
        <>
            <Plot
                data={traces}
                layout={{
                    width: 800,
                    height: 800,
                    title: `Simple 3D Scatter`
                }}
            />
            <h1 className="text-3xl font-bold underline flex-col text-red ">
                <div className="bg-red-200">Hello world!</div>
                <div className="text-blue-500">Hello world!</div>
                <div>Hello world!</div>
            </h1>

            <Map />

            <Box m={2} >Tomato </Box>
            <Box maxW="960px" mx="auto" />
            <Box m={[2, 3]} />
        </>
    )
}
export default App_Aphilome
