import {Marker, Popup} from "react-leaflet";

function Anchor({ name, lat, lon, alt }) {

    return(
        <Marker position={[lat, lon]}>
            <Popup>
                {name}-{alt}
            </Popup>
        </Marker>
    )
}
export default Anchor;