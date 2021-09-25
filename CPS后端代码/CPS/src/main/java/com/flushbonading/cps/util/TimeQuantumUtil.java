package com.flushbonading.cps.util;

import java.util.HashMap;
import java.util.Map;

/**
 * 时间段处理单例工具
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/6/9 20:55
 * @since 1.0.0
 */
public class TimeQuantumUtil {
    /**
     * 存放对应时间段信息
     */
    private Map<Integer, String> map;

    private TimeQuantumUtil() {
        map = new HashMap<>();
        map.put(1, "0-4");
        map.put(2, "4-8");
        map.put(3, "8-12");
        map.put(4, "12-16");
        map.put(5, "16-20");
        map.put(6, "20-24");
    }

    /**
     * 实现单例的处理类
     */
    private static class TimeQuantumUtilHandler {
        private static TimeQuantumUtil timeQuantumUtil = new TimeQuantumUtil();
    }

    /**
     * 获得单例对象
     *
     * @return 返回单例对象
     */
    public static TimeQuantumUtil getInstance() {
        return TimeQuantumUtilHandler.timeQuantumUtil;
    }

    /**
     * 通过timeID得到相应的时间段
     *
     * @param timeID
     * @return
     */
    public String timeQuantum(Integer timeID) {
        return map.get(timeID);
    }

    public String time(int hour) {
        int time = hour / 4 + 1;
        return time + "";
    }

}
