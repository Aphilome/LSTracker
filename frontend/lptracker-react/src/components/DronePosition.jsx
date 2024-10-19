import {Circle, CircleMarker, MapContainer, Polygon, Polyline, Popup, Rectangle, TileLayer} from "react-leaflet";
function DronePosition({positions, color}) {
    const coords = positions.map(i =>
        [i.lat, i.lon]
    );
    const lineOptions = { color: color }
    const dotOptions = { color: color, fill: color, opacity: 0.1 }
    const dronOptions = { color: color, fill: color, opacity: 1 }

    const lastDot = positions[positions.length - 1];

    return(
        <>
            <Polyline pathOptions={lineOptions} positions={coords} />
            {
                coords.map(i => (<CircleMarker radius={10} pathOptions={dotOptions} center={i}/>))
            }
            <CircleMarker pathOptions={dronOptions} center={lastDot}/>
        </>
    );
}
export default DronePosition;

