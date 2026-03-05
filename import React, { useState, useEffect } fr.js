import React, { useState, useEffect } from "react";
import { View, Text, StyleSheet } from "react-native";
import MapView, { Marker, Polyline } from "react-native-maps";

export default function MapScreen() {
  const [vehicleLocation, setVehicleLocation] = useState({
    latitude: 6.8448,  // Default starting location
    longitude: 79.9300,
  });

  const routeCoordinates = [
    { latitude: 6.8445, longitude: 79.9300 }, // Start
    { latitude: 6.8577, longitude: 79.9340 },
    { latitude: 6.8700, longitude: 79.9360 },
    { latitude: 6.8800, longitude: 79.9370 },
    { latitude: 6.8878, longitude: 79.9380 }, // Destination
  ];

  useEffect(() => {
    const fetchGPSData = () => {
      fetch("http://192.168.1.100/gps") // Replace with ESP8266's actual IP
        .then((response) => response.json())
        .then((data) => {
          if (data.latitude && data.longitude) {
            setVehicleLocation({
              latitude: data.latitude,
              longitude: data.longitude,
            });
          }
        })
        .catch((error) => console.error("Error fetching GPS:", error));
    };

    // Fetch data every 3 seconds
    const interval = setInterval(fetchGPSData, 3000);

    return () => clearInterval(interval); // Cleanup interval
  }, []);

  return (
    <View style={styles.container}>
      <MapView
        style={styles.map}
        initialRegion={{
          latitude: vehicleLocation.latitude,
          longitude: vehicleLocation.longitude,
          latitudeDelta: 0.02,
          longitudeDelta: 0.02,
        }}
      >
        {/* Vehicle Marker */}
        <Marker
          coordinate={vehicleLocation}
          title="Vehicle"
          description="Live GPS Location"
        />

        {/* Route (Polyline) */}
        <Polyline
          coordinates={routeCoordinates}
          strokeWidth={5}
          strokeColor="blue"
        />

        {/* Destination Marker */}
        <Marker
          coordinate={routeCoordinates[routeCoordinates.length - 1]}
          title="Destination"
          description="Final Stop"
        />
      </MapView>

      <View style={styles.footer}>
        <Text style={styles.footerText}>
          Latitude: {vehicleLocation.latitude.toFixed(6)}
        </Text>
        <Text style={styles.footerText}>
          Longitude: {vehicleLocation.longitude.toFixed(6)}
        </Text>
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: { flex: 1 },
  map: { flex: 1 },
  footer: {
    position: "absolute",
    bottom: 0,
    left: 0,
    right: 0,
    backgroundColor: "black",
    paddingVertical: 15,
    alignItems: "center",
  },
  footerText: { color: "white", fontSize: 18 },
});
