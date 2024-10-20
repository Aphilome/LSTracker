import Plot from "react-plotly.js";

function PlotMain({dronePositionsUwb, dronePositionsGps}) {

    function randomValues(num, mul) {
        const arr = [];
        const index = [];
        for (let i = 0; i < num; i++) {
            arr.push(Math.random() * mul)
            index.push(i);
        }
        return {index, arr};
    }

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
        <Plot
            data={traces}
            layout={{
                width: 800,
                height: 800,
                title: `Simple 3D Scatter`
            }}
        />
    );
}

export default PlotMain;