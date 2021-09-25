package com.flushbonading.cps.util;

import java.util.HashMap;
import java.util.Map;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/7/8 8:48
 * @since 1.0.0
 */
public class RemarkUtil {
    private Map<String, String> map;

    private RemarkUtil() {
        map = new HashMap<>();
        map.put("1", "清洁、润滑");
        map.put("2", "调整");
        map.put("3", "防腐");
        map.put("4", "检错排故");
    }

    /**
     * 实现单例的处理类
     */
    private static class RemarkUtilHandler {
        private static RemarkUtil remarkUtil = new RemarkUtil();
    }

    public static RemarkUtil getInstance() {
        return RemarkUtilHandler.remarkUtil;
    }

    public String remark(String remarkID) {
        return map.get(remarkID);
    }
}
