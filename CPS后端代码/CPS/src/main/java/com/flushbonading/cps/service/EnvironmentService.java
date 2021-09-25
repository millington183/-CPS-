package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.Environment;
import com.flushbonading.cps.entity.dto.EnvironmentDTO;
import com.flushbonading.cps.entity.vo.EnvironmentVO;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
public interface EnvironmentService extends IService<Environment> {
    /**
     * 查询环境信息
     *
     * @return 返回环境信息对象
     */
    EnvironmentDTO queryEnvironmentMessage();

    /**
     * 查询环境信息
     *
     * @return
     */
    EnvironmentVO getNowEnvironmentVO();
}
