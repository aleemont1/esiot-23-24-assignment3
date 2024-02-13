package org.mqttserver.presentation;

import com.google.gson.Gson;

public class JSONUtils {

    private static final Gson gson = new Gson();

    /**
     * Converts a Java object to its JSON representation.
     *
     * @param object The Java object to be converted to JSON.
     * @return A JSON string representing the json IN STRING Java format
     */
    public static String objectToJson(Object object) {
        return gson.toJson(object);
    }
    /**
     * Converts a JSON string to a Java object of the specified class.
     *
     * @param json The JSON string to be converted to a Java object.
     * @param classOfT The class of the target Java object.
     * @param <T> The type of the target Java object.
     * @return An instance of the specified class representing the input JSON.
     */
    public static <T> T jsonToObject(String json, Class<T> classOfT) {
        return gson.fromJson(json, classOfT);
    }
}
