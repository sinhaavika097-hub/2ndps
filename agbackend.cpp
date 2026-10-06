#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

// Mock structure representing incoming JSON data from field sensors
struct FieldSensorData {
    std::string device_id;
    float temperature_c;    // Celsius
    float humidity_percent; // %
    float soil_moisture;    // %
    float ndvi_score;       // Normalized Difference Vegetation Index (0.0 to 1.0)
};

class AgriTechInferenceEngine {
public:
    // Simulating a deployed Decision Tree / ML Model logic for Pest Risk
    // In production, you would load a TFLite model or ONNX runtime here.
    std::string evaluatePestRisk(const FieldSensorData& data) {
        float risk_score = 0.0f;

        // Certain pests thrive in high heat and specific humidity ranges
        if (data.temperature_c > 28.0 && data.temperature_c < 35.0) {
            risk_score += 0.3f;
        }
        if (data.humidity_percent > 70.0) {
            risk_score += 0.25f;
        }
        
        // A sudden drop in NDVI indicates crop stress/leaf damage
        if (data.ndvi_score < 0.4f) {
            risk_score += 0.45f;
        }

        return formatRiskResponse(risk_score);
    }

    // A simple regression simulation for Crop Yield Health
    float predictYieldHealth(const FieldSensorData& data) {
        // Ideal conditions yield closer to 100% (1.0)
        float moisture_factor = (data.soil_moisture > 40.0f && data.soil_moisture < 60.0f) ? 1.0f : 0.6f;
        float ndvi_factor = data.ndvi_score * 1.5f; // Higher vegetation index is better
        
        float health_index = (moisture_factor * 0.4f) + (ndvi_factor * 0.6f);
        return std::min(health_index, 1.0f) * 100.0f; // Return as percentage
    }

private:
    std::string formatRiskResponse(float risk_score) {
        if (risk_score >= 0.75f) return "CRITICAL: High Pest Probability. Initiate Drone Spraying.";
        if (risk_score >= 0.4f)  return "WARNING: Moderate Stress Detected. Manual Inspection Required.";
        return "SAFE: Nominal Conditions.";
    }
};

// Simulated API Controller handling an incoming POST request
void handleIncomingData(const FieldSensorData& incoming_data) {
    AgriTechInferenceEngine engine;

    std::cout << "\n--- [API Gateway] Received Data from Edge Device: " << incoming_data.device_id << " ---\n";
    std::cout << "Processing Multi-Modal Inputs...\n";

    // 1. Run inference
    std::string pest_alert = engine.evaluatePestRisk(incoming_data);
    float yield_prediction = engine.predictYieldHealth(incoming_data);

    // 2. Output the JSON response (Simulated)
    std::cout << "{\n";
    std::cout << "  \"status\": \"success\",\n";
    std::cout << "  \"device_id\": \"" << incoming_data.device_id << "\",\n";
    std::cout << "  \"analysis\": {\n";
    std::cout << "    \"pest_risk_status\": \"" << pest_alert << "\",\n";
    std::cout << "    \"estimated_yield_health\": \"" << std::fixed << std::setprecision(2) << yield_prediction << "%\"\n";
    std::cout << "  }\n";
    std::cout << "}\n";
}

int main() {
    // Simulating two different data packets coming from different farm nodes
    
    // Node 1: Healthy Farm
    FieldSensorData node_alpha = {"ESP32_NODE_A1", 24.5, 55.0, 50.0, 0.75};
    handleIncomingData(node_alpha);

    // Node 2: Farm under stress (High Temp, High Humidity, Low NDVI indicating leaf loss)
    FieldSensorData node_beta = {"ESP32_NODE_B2", 32.0, 75.0, 30.0, 0.35};
    handleIncomingData(node_beta);

    return 0;
}