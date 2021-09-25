package com.flushbonading.cps.entity;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * 数据下发对象
 *
 * @author zyx 2134208960@qq.com
 * @date 2021/6/23 20:29
 * @since 1.0.0
 */
@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class DataReleased {
    /**
     * 资源ID
     */
    private Integer res_id;
    /**
     * 下发的数据
     */
    private String val;
}
