package com.flushbonading.cps.constant;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/17 10:18
 * @since 1.0.0
 */
public enum Gender {
    /**
     * 男
     */
    MALE("男"),
    /**
     * 女
     */
    FEMALE("女");

    private String gender;

    Gender(String gender) {
        this.gender = gender;
    }

    /**
     * 得到性别值
     *
     * @return
     */
    public String gender() {
        return this.gender;
    }
}
