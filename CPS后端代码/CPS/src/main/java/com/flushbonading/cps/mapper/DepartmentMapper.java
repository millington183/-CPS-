package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.Department;
import com.flushbonading.cps.entity.dto.DepartmentDTO;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

/**
 * <p>
 * Mapper 接口
 * </p>
 *
 * @author zyx
 * @since 2021-06-13
 */
@Mapper
public interface DepartmentMapper extends BaseMapper<Department> {
    /**
     * 得到所有部门
     *
     * @return
     */
    List<DepartmentDTO> getAll();
}
