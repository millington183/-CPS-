package com.flushbonading.cps.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.entity.Environment;
import com.flushbonading.cps.entity.dto.EnvironmentDTO;
import com.flushbonading.cps.entity.vo.EnvironmentVO;
import com.flushbonading.cps.mapper.EnvironmentMapper;
import com.flushbonading.cps.service.EnvironmentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

/**
 * <p>
 * 服务实现类
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
@Service
public class EnvironmentServiceImpl extends ServiceImpl<EnvironmentMapper, Environment> implements EnvironmentService {
    /**
     * 环境映射器
     */
    @Autowired
    EnvironmentMapper environmentMapper;

    /**
     * 查询环境信息
     *
     * @return
     */
    @Override
    public EnvironmentDTO queryEnvironmentMessage() {
        //通过构造器进行查询
        Environment allEnvironmentMessage = environmentMapper.selectById(1);
        //利用建造者模式创建对象
        EnvironmentDTO environmentDTO = EnvironmentDTO.builder()
                .temperature(allEnvironmentMessage.getTemperature())
                .humidity(allEnvironmentMessage.getHumidity())
                .dust(allEnvironmentMessage.getDust())
                .build();
        return environmentDTO;
    }

    @Override
    public EnvironmentVO getNowEnvironmentVO() {
        return environmentMapper.getNowEnvironmentVO();
    }
}
