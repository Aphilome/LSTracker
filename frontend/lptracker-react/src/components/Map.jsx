import {MapContainer, Marker, Popup, TileLayer} from 'react-leaflet'
import 'leaflet/dist/leaflet.css'
import Anchor from "./Anchor";
import {useState} from "react";
import {ANCHORS} from "../anchors";

function Map() {
    const [anchors, setAnchors] = useState(ANCHORS);

    return(
        <MapContainer className='w-80 h-80' center={[51.505, -0.09]} zoom={13} >
            <TileLayer
                attribution='&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
                url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
            />
            {
                anchors.map(i => (
                    <Anchor key={i.name} alt={i.alt} lon={i.lon} lat={i.lat} name={i.name}/>
                ))
            }

        </MapContainer>
    );
}

export default Map;