package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.Post;
import com.flushbonading.cps.entity.dto.PostDTO;
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
public interface PostMapper extends BaseMapper<Post> {
    /**
     * 根据部门查找所有的职务
     *
     * @param departmentName
     * @return
     */
    List<PostDTO> getPostByDepartment(String departmentName);
}
