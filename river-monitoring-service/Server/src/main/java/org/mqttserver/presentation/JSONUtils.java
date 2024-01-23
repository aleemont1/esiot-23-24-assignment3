package org.mqttserver.presentation;

import com.google.gson.Gson;

public class JSONUtils {

    private static final Gson gson = new Gson();

    public static String objectToJson(Object object) {
        return gson.toJson(object);
    }

    public static <T> T jsonToObject(String json, Class<T> classOfT) {
        return gson.fromJson(json, classOfT);
    }
}
