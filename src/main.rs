use serde::{Deserialize, Serialize};
use serde_cbor;
use serde_json;
use warp::{hyper::body, Filter};

#[derive(Deserialize, Serialize, Debug)]
struct TelemetryData {
    version: String,
    rssi: i32,
}

#[derive(Deserialize, Serialize)]
struct TelemetryError {
    error: String,
}

#[tokio::main]
async fn main() {
    // POST /telemetry/:id  {"version":"0.1.0","rssi":-49}
    let telemetry = warp::post()
        .and(warp::path("telemetry"))
        .and(warp::path::param::<String>())
        .and(warp::body::content_length_limit(1024))
        .and(warp::body::bytes())
        .map(|id, data: body::Bytes| {
            println!("Message from id: {} size: {} bytes", id, data.len());

            // Get the telemetry
            let telemetry: TelemetryData = match serde_cbor::from_slice(&data) {
                Ok(t) => t,
                Err(_) => {
                    // Create error
                    let error = TelemetryError {
                        error: "Unable to parse CBOR telemetry data.".to_string(),
                    };

                    // Return error
                    return warp::reply::json(&error);
                }
            };

            println!("Telemetry: {:?}", telemetry);

            // Now encode to json
            let json = match serde_json::to_string(&telemetry) {
                Ok(j) => j,
                Err(_) => {
                    // Create error
                    let error = TelemetryError {
                        error: "Unable to parse telemetry data to JSON.".to_string(),
                    };

                    // Return error
                    return warp::reply::json(&error);
                }
            };
            println!("JSON message size: {} bytes", json.len());

            warp::reply::json(&{})
        });

    warp::serve(telemetry).run(([127, 0, 0, 1], 3030)).await
}
