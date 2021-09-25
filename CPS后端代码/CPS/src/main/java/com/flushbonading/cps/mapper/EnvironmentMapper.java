package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.Environment;
import com.flushbonading.cps.entity.vo.EnvironmentVO;
import org.apache.ibatis.annotations.Mapper;

/**
 * <p>
 * Mapper 接口
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
@Mapper
public interface EnvironmentMapper extends BaseMapper<Environment> {
    /**
     * 修改环境数据
     *
     * @param dust
     * @param humidity
     * @param temperature
     * @return
     */
    Integer updateEnvironment(String dust, String humidity, String temperature);

    /**
     * 查询环境信息
     *
     * @return
     */
    EnvironmentVO getNowEnvironmentVO();
}
