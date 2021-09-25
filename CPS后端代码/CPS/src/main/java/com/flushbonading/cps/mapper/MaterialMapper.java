package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.Material;
import com.flushbonading.cps.entity.vo.MaterialVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * Mapper 接口
 * </p>
 *
 * @author zyx
 * @since 2021-06-17
 */
@Mapper
public interface MaterialMapper extends BaseMapper<Material> {
    /**
     * 展示物料
     *
     * @param materialId
     * @param page
     * @return
     */
    List<MaterialVO> showMaterials(String materialId, Integer page);

    /**
     * 物料数
     *
     * @param materialId
     * @return
     */
    Integer materialCounts(String materialId);

    /**
     * 插入一个物料
     *
     * @param material
     * @return
     */
    Integer addAMaterial(@Param("material") MaterialVO material);

    /**
     * 通过物料id删除物料
     *
     * @param materialId
     * @return
     */
    Integer deleteAMaterialByMaterialId(String materialId);

    /**
     * 修改物料
     *
     * @param material
     * @return
     */
    Integer updateAMaterial(@Param("material") MaterialVO material);

    /**
     * 得到所有物料名称
     *
     * @return
     */
    List<String> getBrandName();
}
